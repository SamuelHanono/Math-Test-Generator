#ifndef TEX_PROBLEM_BANK_READER_H
#define TEX_PROBLEM_BANK_READER_H

#include "problem_bank_reader.h"
#include "problem.h"

class TexProblemBankReader : public ProblemBankReader {
public:
    std::vector<std::unique_ptr<IProblem>>
    readProblems(const std::string& filename) const override;
};

#endif
