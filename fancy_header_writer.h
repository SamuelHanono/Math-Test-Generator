#ifndef FANCY_HEADER_WRITER_H
#define FANCY_HEADER_WRITER_H

#include "header_writer.h"
#include <string>

class FancyHeaderWriter : public HeaderWriter {
public:
    FancyHeaderWriter(const std::string& texHeader,
                      const std::string& contentHeader,
                      const std::string& className,
                      const std::string& term,
                      const std::string& examNo,
                      const std::string& timeOfDay,
                      const std::string& formLetter,
                      const std::string& title,
                      int numProblems);

    void writeHeader(std::ostream& out) const override;

private:
    std::string texHeader;
    std::string contentHeader;
    std::string className;
    std::string term;
    std::string examNo;
    std::string timeOfDay;
    std::string formLetter;
    std::string title;
    int numProblems;
};

#endif
