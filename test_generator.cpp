#include "test_generator.h"
#include <fstream>
#include <stdexcept>

void TestGenerator::generate(const std::string& bankFile,
                             const std::string& outputFile,
                             int numProblems,
                             std::vector<std::unique_ptr<Constraint>>& constraints) {
    auto problems = reader->readProblems(bankFile);
    auto chosen   = selector->selectProblems(problems, numProblems, constraints);

    std::ofstream out(outputFile);
    if (!out.is_open()) {
        throw std::runtime_error("Unable to open output file");
    }

    headerWriter->writeHeader(out);
    layout->writeProblems(out, chosen);
}
