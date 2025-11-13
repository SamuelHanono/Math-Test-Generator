#include "fancy_header_writer.h"

FancyHeaderWriter::FancyHeaderWriter(const std::string& texHeader,
                                     const std::string& contentHeader,
                                     const std::string& className,
                                     const std::string& term,
                                     const std::string& examNo,
                                     const std::string& timeOfDay,
                                     const std::string& formLetter,
                                     const std::string& title,
                                     int numProblems)
    : texHeader(texHeader),
      contentHeader(contentHeader),
      className(className),
      term(term),
      examNo(examNo),
      timeOfDay(timeOfDay),
      formLetter(formLetter),
      title(title),
      numProblems(numProblems) {}

void FancyHeaderWriter::writeHeader(std::ostream& out) const {
    // This reproduces the old fancy_test_generator behavior:
    // \input{fancy_tex_header}
    out << "\\input{" << texHeader << "}\n";

    // Manually-entered info
    out << "\\newcommand{\\class}{" << className << "}\n";
    out << "\\newcommand{\\term}{" << term << "}\n";
    out << "\\newcommand{\\examno}{" << examNo << "}\n";
    out << "\\newcommand{\\dayeve}{" << timeOfDay << "}\n";
    out << "\\newcommand{\\formletter}{" << formLetter << "}\n";
    out << "\\newcommand{\\numproblems}{" << numProblems << " }\n";
    out << "\\newcommand{\\testtitle}{" << title << "}\n";

    // Then include the content header
    out << "\\input{" << contentHeader << "}\n";
}

