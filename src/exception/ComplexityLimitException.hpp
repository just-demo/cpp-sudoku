#pragma once

#include <stdexcept>

namespace just::demo::exception {
    class ComplexityLimitException : public std::runtime_error {
    public:
        ComplexityLimitException() : std::runtime_error("Complexity limit exceeded") {
        }
    };
}
