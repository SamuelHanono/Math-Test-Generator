#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <vector>
#include "iproblem.h"

class Constraint {
public:
    virtual ~Constraint() = default;

    virtual bool isSatisfied(const std::vector<IProblem*>& chosen) const = 0;
};

#endif
