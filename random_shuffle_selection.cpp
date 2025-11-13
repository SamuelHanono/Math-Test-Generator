#include "random_shuffle_selection.h"
#include <random>
#include <algorithm>

std::vector<IProblem*>
RandomShuffleSelection::selectProblems(
        const std::vector<std::unique_ptr<IProblem>>& pool,
        int numProblems,
        const std::vector<std::unique_ptr<Constraint>>& constraints) {

    std::vector<IProblem*> candidates;
    candidates.reserve(pool.size());
    for (auto &p : pool) {
        candidates.push_back(p.get());
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    while (true) {
        std::shuffle(candidates.begin(), candidates.end(), gen);

        std::vector<IProblem*> chosen(candidates.begin(), candidates.begin() + numProblems);

        bool ok = true;
        for (const auto &c : constraints) {
            if (!c->isSatisfied(chosen)) {
                ok = false;
                break;
            }
        }
        if (ok) return chosen;
    }
}
