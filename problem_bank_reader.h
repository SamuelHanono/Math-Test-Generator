#ifndef PROBLEM_BANK_READER_H
#define PROBLEM_BANK_READER_H

#include <string>
#include <vector>
#include <memory>
#include "iproblem.h"

class ProblemBankReader {
public:
    virtual ~ProblemBankReader() = default;

    virtual std::vector<std::unique_ptr<IProblem>>
    readProblems(const std::string& filename) const = 0;
};

#endif
