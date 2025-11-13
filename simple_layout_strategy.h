#ifndef SIMPLE_LAYOUT_STRATEGY_H
#define SIMPLE_LAYOUT_STRATEGY_H

#include "layout_strategy.h"

class SimpleLayoutStrategy : public LayoutStrategy {
public:
    void writeProblems(std::ostream& out,
                       const std::vector<IProblem*>& problems) const override;
};

#endif
