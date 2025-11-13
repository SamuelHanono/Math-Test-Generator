#ifndef DIFFICULTY_CONSTRAINT_H
#define DIFFICULTY_CONSTRAINT_H

#include "constraint.h"
#include "problem.h"

class DifficultyConstraint : public Constraint {
public:
    DifficultyConstraint(int minSum, int maxSum)
        : minSum(minSum), maxSum(maxSum) {}

    bool isSatisfied(const std::vector<IProblem*>& chosen) const override;

private:
    int minSum;
    int maxSum;
};

#endif
