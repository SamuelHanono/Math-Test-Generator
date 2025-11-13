#include <memory>
#include <string>
#include <vector>

#include "test_generator.h"
#include "tex_problem_bank_reader.h"
#include "random_shuffle_selection.h"
#include "fancy_header_writer.h"
#include "fancy_layout_strategy.h"
#include "difficulty_constraint.h"
#include "topic_count_constraint.h"

// ****************************************************************************
// Configuration details

// Variable information to be printed on the test
std::string CLASS = "Arithmetic";
std::string TERM  = "Fall 2025";
std::string EXAM  = "925";
std::string TIME  = "Day";
std::string TITLE = "Final Exam";
std::string FORM  = "A";

// Source file for problem bank
std::string BANK = "arithmetic_problems.tex";

// Filename for the created test
std::string FILENAME = "fancy_test.tex";

// Constraints on the problem choice.
int NUM_PROBLEMS    = 20; // The test must have 20 problems.
int MIN_TOPIC       = 3;  // Each topic must be covered 
int MAX_TOPIC       = 7;  // by 3-7 problems.
int MIN_DIFFICULTY  = 65; // Total difficulty must be 65-75.
int MAX_DIFFICULTY  = 75;

// tex files to include in the test file
std::string TEX_HEADER     = "fancy_tex_header.tex";
std::string CONTENT_HEADER = "fancy_content_header.tex";

// ****************************************************************************

int main() {
    // Wire up the pluggable components
    auto reader   = std::make_unique<TexProblemBankReader>();
    auto selector = std::make_unique<RandomShuffleSelection>();
    auto header   = std::make_unique<FancyHeaderWriter>(
        TEX_HEADER,
        CONTENT_HEADER,
        CLASS,
        TERM,
        EXAM,
        TIME,
        FORM,
        TITLE,
        NUM_PROBLEMS
    );
    auto layout   = std::make_unique<FancyLayoutStrategy>();

    // Build the constraints
    std::vector<std::unique_ptr<Constraint>> constraints;

    // Difficulty constraint
    constraints.push_back(
        std::make_unique<DifficultyConstraint>(
            MIN_DIFFICULTY,
            MAX_DIFFICULTY
        )
    );

    // Topic count constraints – topics from arithmetic_problems.tex
    constraints.push_back(
        std::make_unique<TopicCountConstraint>(
            "addition",
            MIN_TOPIC,
            MAX_TOPIC
        )
    );
    constraints.push_back(
        std::make_unique<TopicCountConstraint>(
            "subtraction",
            MIN_TOPIC,
            MAX_TOPIC
        )
    );
    constraints.push_back(
        std::make_unique<TopicCountConstraint>(
            "multiplication",
            MIN_TOPIC,
            MAX_TOPIC
        )
    );
    constraints.push_back(
        std::make_unique<TopicCountConstraint>(
            "division",
            MIN_TOPIC,
            MAX_TOPIC
        )
    );

    // Core generator
    TestGenerator generator(
        std::move(reader),
        std::move(selector),
        std::move(header),
        std::move(layout)
    );

    // Generate the test
    generator.generate(BANK, FILENAME, NUM_PROBLEMS, constraints);

    return 0;
}
