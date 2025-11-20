// fancy_topic_author_length.cpp
// Generates a 10-problem fancy test from math_problems.tex
// with constraints on author/topic/length using a greedy algorithm.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <cctype>

// One problem from the bank
struct Problem {
    std::string question;
    std::string answer;
    std::string topic;
    std::string author;
    bool isLong = false;
};

// Basic whitespace trim (left + right)
std::string trim(const std::string& s) {
    std::size_t start = 0;
    while (start < s.size() &&
           std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }

    std::size_t end = s.size();
    while (end > start &&
           std::isspace(static_cast<unsigned char>(s[end - 1]))) {
        --end;
    }

    return s.substr(start, end - start);
}

// Extract stuff inside { ... } on a line like \command{this part}
std::string extract_braces(const std::string& line) {
    std::size_t open = line.find('{');
    std::size_t close = line.rfind('}');
    if (open == std::string::npos ||
        close == std::string::npos ||
        close <= open) {
        return "";
    }
    return line.substr(open + 1, close - open - 1);
}

// Read math_problems.tex into a vector of Problem
std::vector<Problem> parse_math_problems(const std::string& filename) {
    std::ifstream in(filename);
    std::vector<Problem> problems;

    if (!in) {
        std::cerr << "Could not open " << filename << " for reading.\n";
        return problems;
    }

    std::string line;
    bool inItem = false;
    Problem current;

    while (std::getline(in, line)) {
        std::string trimmed = trim(line);

        // Start of new problem
        if (trimmed.rfind("\\item", 0) == 0) {
            // Save previous problem if we were in one
            if (inItem) {
                problems.push_back(current);
            }
            inItem = true;
            current = Problem();

            // Everything after "\item" is part of the question text
            std::string rest = trimmed.substr(5); // len("\item") == 5
            current.question = trim(rest);
        }
        // Answer line
        else if (inItem && trimmed.rfind("\\answer", 0) == 0) {
            current.answer = trim(extract_braces(trimmed));
        }
        // Topic line
        else if (inItem && trimmed.rfind("\\topic", 0) == 0) {
            current.topic = trim(extract_braces(trimmed));
        }
        // Author line
        else if (inItem && trimmed.rfind("\\author", 0) == 0) {
            current.author = trim(extract_braces(trimmed));
        }
        // isLong line
        else if (inItem && trimmed.rfind("\\isLong", 0) == 0) {
            std::string val = trim(extract_braces(trimmed));
            current.isLong = (val == "true" || val == "True" || val == "TRUE");
        }
        // Extra text inside the problem (more lines of question)
        else if (inItem) {
            if (!current.question.empty()) {
                current.question += "\n";
            }
            current.question += line;
        }
    }

    // Push the last problem if file ended inside an item
    if (inItem) {
        problems.push_back(current);
    }

    return problems;
}

// Try to build ONE valid test using the greedy algorithm
bool build_one_test(const std::vector<Problem>& bank,
                    std::vector<Problem>& chosen,
                    std::mt19937& rng) {
    const int targetNumProblems = 10;

    // Randomly choose 3 or 4 long problems as the target
    std::uniform_int_distribution<int> longDist(0, 1);
    int targetLong = (longDist(rng) == 0) ? 3 : 4;

    // Work on a shuffled copy of the bank
    std::vector<Problem> shuffled = bank;
    std::shuffle(shuffled.begin(), shuffled.end(), rng);

    chosen.clear();
    std::map<std::string, int> authorCount;
    std::map<std::string, int> topicCount;
    int longCount = 0;

    // Greedy pass
    for (const Problem& p : shuffled) {
        if ((int)chosen.size() == targetNumProblems) {
            break;
        }

        int aCount = authorCount[p.author];
        int tCount = topicCount[p.topic];
        int newLongCount = longCount + (p.isLong ? 1 : 0);

        // Enforce upper bounds
        if (aCount >= 2) continue;
        if (tCount >= 2) continue;
        if (newLongCount > targetLong) continue;

        // Take this problem
        chosen.push_back(p);
        authorCount[p.author] = aCount + 1;
        topicCount[p.topic]  = tCount + 1;
        longCount = newLongCount;
    }

    // Check total count
    if ((int)chosen.size() != targetNumProblems) {
        return false;
    }

    // Check long count
    if (longCount != targetLong) {
        return false;
    }

    // Check every author has 1–2 problems
    for (const auto& entry : authorCount) {
        int c = entry.second;
        if (c < 1 || c > 2) {
            return false;
        }
    }

    // Check every topic has 1–2 problems
    for (const auto& entry : topicCount) {
        int c = entry.second;
        if (c < 1 || c > 2) {
            return false;
        }
    }

    return true;
}

// Write the fancy LaTeX test
// Short problems: two per page (top + bottom) when possible
// Long problems: one per page
void write_fancy_test(const std::string& outFile,
                      std::vector<Problem> problems) {
    // Sort so short problems come first, then long problems
    std::stable_sort(problems.begin(), problems.end(),
                     [](const Problem& a, const Problem& b) {
                         return a.isLong < b.isLong;  // false (short) before true (long)
                     });

    std::ofstream out(outFile, std::ofstream::out | std::ofstream::trunc);
    if (!out) {
        std::cerr << "Could not open " << outFile << " for writing.\n";
        return;
    }

    // Header: plug into your existing fancy LaTeX headers
    out << "\\input{fancy_tex_header.tex}\n";
    out << "\\newcommand{\\testtitle}{Advanced Math Test}\n";
    out << "\\input{fancy_content_header.tex}\n";
    out << "\\begin{document}\n";
    out << "\\begin{enumerate}\n\n";

    // Separate into shorts and longs
    std::vector<Problem> shorts;
    std::vector<Problem> longs;

    for (const Problem& p : problems) {
        if (p.isLong) longs.push_back(p);
        else          shorts.push_back(p);
    }

    // Short problems: 2 per page
    for (std::size_t i = 0; i < shorts.size(); ++i) {
        const Problem& p = shorts[i];

        // Sanitize question text: remove any accidental '\\end{document}' and trim
        std::string q = p.question;
        std::size_t edpos = q.find("\\end{document}");
        if (edpos != std::string::npos) q.erase(edpos);
        out << "\\item " << q << "\n\n";

        bool isSecondOnPage = (i % 2 == 1);
        bool isLastShort    = (i == shorts.size() - 1);

        if (isSecondOnPage || isLastShort) {
            // End page after second problem or last short problem
            out << "\\newpage\n\n";
        } else {
            // Fill the rest of the page so the next short problem goes on bottom half
            out << "\\vfill\n\n";
        }
    }

    // Long problems: 1 per page
    for (std::size_t i = 0; i < longs.size(); ++i) {
        const Problem& p = longs[i];

        // Ensure each long problem starts on a new page
        out << "\\newpage\n";
        out << "\\item " << p.question << "\n\n";
    }

    out << "\\end{enumerate}\n";
    out << "\\end{document}\n";
}

int main() {
    // 1. Read the problem bank
    std::vector<Problem> bank = parse_math_problems("math_problems.tex");
    if (bank.empty()) {
        std::cerr << "No problems parsed from math_problems.tex\n";
        return 1;
    }

    // 2. Set up RNG
    std::random_device rd;
    std::mt19937 rng(rd());

    // 3. Try to build a valid test a few times
    std::vector<Problem> chosen;
    const int maxTries = 1000;
    bool success = false;

    for (int attempt = 0; attempt < maxTries; ++attempt) {
        if (build_one_test(bank, chosen, rng)) {
            success = true;
            break;
        }
    }

    if (!success) {
        std::cerr << "Failed to build a valid test after "
                  << maxTries << " attempts.\n";
        return 1;
    }

    // 4. Write the LaTeX output
    write_fancy_test("fancy_topic_author_length.tex", chosen);
    std::cout << "Wrote fancy_topic_author_length.tex\n";

    return 0;
}
