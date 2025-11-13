#include "fancy_layout_strategy.h"

void FancyLayoutStrategy::writeProblems(std::ostream& out,
                                        const std::vector<IProblem*>& problems) const {
    int problem_number = 1;

    for (IProblem* ip : problems) {
        // This reproduces the original layout logic:
        // odd-numbered problems: start a new page
        // even-numbered problems: insert big vertical space
        if (problem_number % 2 == 1) {
            out << "\\pagebreak\n\n";
        } else {
            out << "\\vspace{350pt}\n\n";
        }

        out << "\\item\\begin{tabular}[t]{p{5in} p{.3in} p{.8in}}\n";
        out << ip->getQuestion();
        out << "& & \\arabic{enumi}.\\hrulefill\n\\end{tabular}\n";

        ++problem_number;
    }

    // End the file like the old fancy generator
    out << "\\end{enumerate}\n\\end{document}";
}
