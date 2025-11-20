// simple_with_answers.cpp
// Generates a basic arithmetic test with \question{...} and \answer{...}
// from arithmetic_problems.tex

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// Simple struct to hold one problem
struct Problem {
    std::string question;
    std::string answer;
};

// Trim whitespace from both ends (basic, human version)
std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }
    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) {
        --end;
    }
    return s.substr(start, end - start);
}

// Extract the text inside {...} for a line like \answer{something}
std::string extract_braces(const std::string& line) {
    std::size_t open = line.find('{');
    std::size_t close = line.rfind('}');
    if (open == std::string::npos || close == std::string::npos || close <= open) {
        return "";
    }
    return line.substr(open + 1, close - open - 1);
}

// Parse arithmetic_problems.tex into a vector of Problem
std::vector<Problem> parse_arithmetic_problems(const std::string& filename) {
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

        // Start of a new problem
        if (trimmed.rfind("\\item", 0) == 0) {
            // If we were already inside a problem, save it
            if (inItem) {
                problems.push_back(current);
            }
            inItem = true;
            current = Problem();

            // Everything after "\item" is part of the question text
            std::string rest = trimmed.substr(5); // length of "\item"
            current.question = trim(rest);
        }
        // Answer line inside a problem
        else if (inItem && trimmed.rfind("\\answer", 0) == 0) {
            current.answer = trim(extract_braces(trimmed));
        }
        // Any extra lines inside the problem, treat as additional question text
        else if (inItem) {
            if (!current.question.empty()) {
                current.question += "\n";
            }
            current.question += line; // keep original formatting
        }
    }

    // Push the last problem if we were in one
    if (inItem) {
        problems.push_back(current);
    }

    return problems;
}

// Write the LaTeX test with \question{} and \answer{}
void write_simple_test_with_answers(const std::string& outFile,
                                    const std::vector<Problem>& problems) {
    std::ofstream out(outFile);
    if (!out) {
        std::cerr << "Could not open " << outFile << " for writing.\n";
        return;
    }

    // Header as in the assignment
    out << "\\input{questions_tex_header.tex}\n";
    out << "\\newcommand{\\testtitle}{Arithmetic Test}\n";
    out << "\\input{simple_content_header.tex}\n";
    out << "\\begin{document}\n";
    out << "\\begin{enumerate}\n\n";

    for (const Problem& p : problems) {
        out << "\\item \\question{ " << p.question << " }\n";
        out << "\\answer{" << p.answer << "}\n\n";
    }

    out << "\\end{enumerate}\n";
    out << "\\end{document}\n";
}

int main() {
    // 1. Read problems from arithmetic_problems.tex
    std::vector<Problem> problems = parse_arithmetic_problems("arithmetic_problems.tex");

    if (problems.empty()) {
        std::cerr << "No problems parsed. Check arithmetic_problems.tex format.\n";
        return 1;
    }

    // 2. Write the test with answers embedded
    write_simple_test_with_answers("simple_with_answers.tex", problems);

    std::cout << "Wrote simple_with_answers.tex\n";
    return 0;
}
