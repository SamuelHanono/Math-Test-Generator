#include "topic_count_constraint.h"

bool TopicCountConstraint::isSatisfied(const std::vector<IProblem*>& chosen) const {
    int count = 0;
    for (IProblem* ip : chosen) {
        auto* p = dynamic_cast<Problem*>(ip);
        if (p && p->getTopic() == topic) {
            ++count;
        }
    }
    return count >= minCount && count <= maxCount;
}
