#include <memory>
#include <vector>
#include <string>
#include "test_generator.h"
#include "tex_problem_bank_reader.h"
#include "random_shuffle_selection.h"
#include "simple_header_writer.h"
#include "simple_layout_strategy.h"
#include "difficulty_constraint.h"
#include "topic_count_constraint.h"

// Configuration details (same as original)
std::string TITLE = "Arithmetic Test";
std::string BANK = "arithmetic_problems.tex";
std::string FILENAME = "simple_test.tex";
int NUM_PROBLEMS = 20;
int MIN_TOPIC = 3;
int MAX_TOPIC = 7;
int MIN_DIFFICULTY = 65;
int MAX_DIFFICULTY = 75;
std::string TEX_HEADER = "simple_tex_header.tex";
std::string CONTENT_HEADER = "simple_content_header.tex";

int main() {
    auto reader   = std::make_unique<TexProblemBankReader>();
    auto selector = std::make_unique<RandomShuffleSelection>();
    auto header   = std::make_unique<SimpleHeaderWriter>(
        TEX_HEADER, CONTENT_HEADER, TITLE);
    auto layout   = std::make_unique<SimpleLayoutStrategy>();

    std::vector<std::unique_ptr<Constraint>> constraints;
    constraints.push_back(std::make_unique<DifficultyConstraint>(
        MIN_DIFFICULTY, MAX_DIFFICULTY));

    // one topic constraint per operation in the bank
    constraints.push_back(std::make_unique<TopicCountConstraint>(
        "addition", MIN_TOPIC, MAX_TOPIC));
    constraints.push_back(std::make_unique<TopicCountConstraint>(
        "subtraction", MIN_TOPIC, MAX_TOPIC));
    constraints.push_back(std::make_unique<TopicCountConstraint>(
        "multiplication", MIN_TOPIC, MAX_TOPIC));
    constraints.push_back(std::make_unique<TopicCountConstraint>(
        "division", MIN_TOPIC, MAX_TOPIC));

    TestGenerator gen(std::move(reader),
                      std::move(selector),
                      std::move(header),
                      std::move(layout));

    gen.generate(BANK, FILENAME, NUM_PROBLEMS, constraints);
}