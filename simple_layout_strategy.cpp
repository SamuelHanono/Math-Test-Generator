#include "simple_layout_strategy.h"

void SimpleLayoutStrategy::writeProblems(
        std::ostream& out,
        const std::vector<IProblem*>& problems) const {
    for (IProblem* p : problems) {
        out << "\\item " << p->getQuestion() << "\n";
    }
    out << "\\end{enumerate}\n\\end{document}";
}
