#ifndef TOPIC_COUNT_CONSTRAINT_H
#define TOPIC_COUNT_CONSTRAINT_H

#include "constraint.h"
#include "problem.h"
#include <string>

class TopicCountConstraint : public Constraint {
public:
    TopicCountConstraint(const std::string& topic, int minCount, int maxCount)
        : topic(topic), minCount(minCount), maxCount(maxCount) {}

    bool isSatisfied(const std::vector<IProblem*>& chosen) const override;

private:
    std::string topic;
    int minCount;
    int maxCount;
};

#endif
