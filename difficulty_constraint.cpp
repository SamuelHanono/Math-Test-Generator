#include "difficulty_constraint.h"

bool DifficultyConstraint::isSatisfied(const std::vector<IProblem*>& chosen) const {
    int sum = 0;
    for (IProblem* ip : chosen) {
        auto* p = dynamic_cast<Problem*>(ip);
        if (p) sum += p->getDifficulty();
    }
    return sum >= minSum && sum <= maxSum;
}
