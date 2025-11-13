#include "simple_header_writer.h"

void SimpleHeaderWriter::writeHeader(std::ostream& out) const {
    out << "\\input{" << texHeader << "}\n";
    out << "\\newcommand{\\testtitle}{" << title << "}\n";
    out << "\\input{" << contentHeader << "}\n";
}
