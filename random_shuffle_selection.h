#ifndef RANDOM_SHUFFLE_SELECTION_H
#define RANDOM_SHUFFLE_SELECTION_H

#include "selection_strategy.h"

class RandomShuffleSelection : public SelectionStrategy {
public:
    std::vector<IProblem*>
    selectProblems(const std::vector<std::unique_ptr<IProblem>>& pool,
                   int numProblems,
                   const std::vector<std::unique_ptr<Constraint>>& constraints) override;
};

#endif
