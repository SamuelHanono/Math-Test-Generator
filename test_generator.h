#ifndef TEST_GENERATOR_H
#define TEST_GENERATOR_H

#include <string>
#include <memory>
#include <vector>
#include "problem_bank_reader.h"
#include "selection_strategy.h"
#include "header_writer.h"
#include "layout_strategy.h"
#include "constraint.h"

class TestGenerator {
public:
    TestGenerator(std::unique_ptr<ProblemBankReader> reader,
                  std::unique_ptr<SelectionStrategy> selector,
                  std::unique_ptr<HeaderWriter> headerWriter,
                  std::unique_ptr<LayoutStrategy> layout)
        : reader(std::move(reader)),
          selector(std::move(selector)),
          headerWriter(std::move(headerWriter)),
          layout(std::move(layout)) {}

    void generate(const std::string& bankFile,
                  const std::string& outputFile,
                  int numProblems,
                  std::vector<std::unique_ptr<Constraint>>& constraints);

private:
    std::unique_ptr<ProblemBankReader> reader;
    std::unique_ptr<SelectionStrategy> selector;
    std::unique_ptr<HeaderWriter> headerWriter;
    std::unique_ptr<LayoutStrategy> layout;
};

#endif
