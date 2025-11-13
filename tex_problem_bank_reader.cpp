#include "tex_problem_bank_reader.h"
#include <vector>
#include <memory>

std::vector<std::unique_ptr<IProblem>>
TexProblemBankReader::readProblems(const std::string& filename) const {
    std::vector<std::unique_ptr<IProblem>> result;

    // reuse existing parser
    std::vector<Problem> problems = Problem::problemList(filename);

    for (const auto &p : problems) {
        result.push_back(std::make_unique<Problem>(p));
    }
    return result;
}
