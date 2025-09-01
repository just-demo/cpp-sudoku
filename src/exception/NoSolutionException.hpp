#pragma once

#include <stdexcept>

namespace just::demo::exception {
    class NoSolutionException : public std::runtime_error {
    public:
        NoSolutionException() : std::runtime_error("No solution found") {
        }
    };
}
