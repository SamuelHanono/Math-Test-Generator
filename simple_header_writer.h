#ifndef SIMPLE_HEADER_WRITER_H
#define SIMPLE_HEADER_WRITER_H

#include "header_writer.h"
#include <string>

class SimpleHeaderWriter : public HeaderWriter {
public:
    SimpleHeaderWriter(const std::string& texHeader,
                       const std::string& contentHeader,
                       const std::string& title)
        : texHeader(texHeader), contentHeader(contentHeader), title(title) {}

    void writeHeader(std::ostream& out) const override;

private:
    std::string texHeader;
    std::string contentHeader;
    std::string title;
};

#endif
