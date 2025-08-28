#pragma once

#include <stdexcept>

namespace sudoku {
    class MultipleSolutionsException : public std::runtime_error {
    public:
        MultipleSolutionsException() : std::runtime_error("Multiple solutions found") {
        }
    };

    class NoSolutionException : public std::runtime_error {
    public:
        NoSolutionException() : std::runtime_error("No solution exists") {
        }
    };

    class InterruptedException : public std::runtime_error {
    public:
        InterruptedException() : std::runtime_error("Operation was interrupted") {
        }
    };

    class ComplexityLimitException : public std::runtime_error {
    public:
        ComplexityLimitException() : std::runtime_error("Complexity limit exceeded") {
        }
    };
}
