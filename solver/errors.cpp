#include "errors.hpp"
#include "cell.hpp"
#include "value.hpp"

CannotOpenWithoutGuessingException::CannotOpenWithoutGuessingException(Cell* cell, Value* value)
    : std::runtime_error("Cannot open without guessing"), cell_(cell), value_(value) {}
