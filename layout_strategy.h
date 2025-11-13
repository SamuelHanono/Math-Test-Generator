#ifndef LAYOUT_STRATEGY_H
#define LAYOUT_STRATEGY_H

#include <ostream>
#include <vector>
#include "iproblem.h"

class LayoutStrategy {
public:
    virtual ~LayoutStrategy() = default;

    virtual void writeProblems(std::ostream& out, const std::vector<IProblem*>& problems) const = 0;
};

#endif
