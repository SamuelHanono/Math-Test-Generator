#ifndef HEADER_WRITER_H
#define HEADER_WRITER_H

#include <ostream>

class HeaderWriter {
public:
    virtual ~HeaderWriter() = default;
    virtual void writeHeader(std::ostream& out) const = 0;
};

#endif
