#pragma once
#include <stdexcept>
#include <string>

// Forward declarations
class Cell;
class Value;

class NoSolutionException : public std::runtime_error {
public:
    NoSolutionException() : std::runtime_error("No solution exists") {}
};

class MultipleSolutionsException : public std::runtime_error {
public:
    MultipleSolutionsException() : std::runtime_error("Multiple solutions exist") {}
};

class CannotOpenWithoutGuessingException : public std::runtime_error {
public:
    CannotOpenWithoutGuessingException(Cell* cell, Value* value);
    Cell* getCell() const { return cell_; }
    Value* getValue() const { return value_; }
private:
    Cell* cell_;
    Value* value_;
};
