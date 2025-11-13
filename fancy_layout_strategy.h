#ifndef FANCY_LAYOUT_STRATEGY_H
#define FANCY_LAYOUT_STRATEGY_H

#include "layout_strategy.h"

class FancyLayoutStrategy : public LayoutStrategy {
public:
    void writeProblems(std::ostream& out,
                       const std::vector<IProblem*>& problems) const override;
};

#endif

