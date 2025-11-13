#ifndef SELECTION_STRATEGY_H
#define SELECTION_STRATEGY_H

#include <vector>
#include <memory>
#include "iproblem.h"
#include "constraint.h"

class SelectionStrategy {
public:
    virtual ~SelectionStrategy() = default;

    virtual std::vector<IProblem*>
    selectProblems(const std::vector<std::unique_ptr<IProblem>>& pool,
                   int numProblems,
                   const std::vector<std::unique_ptr<Constraint>>& constraints) = 0;
};

#endif
