#pragma once

#include <stdexcept>
#include <string>

namespace sudoku {

class MultipleSolutionsException : public std::runtime_error {
public:
    MultipleSolutionsException() : std::runtime_error("Multiple solutions found") {}
};

class NoSolutionException : public std::runtime_error {
public:
    NoSolutionException() : std::runtime_error("No solution exists") {}
};

class TimeLimitException : public std::runtime_error {
public:
    TimeLimitException() : std::runtime_error("Time limit exceeded") {}
};

} // namespace sudoku
