#pragma once

#include <stdexcept>

namespace just::demo::exception {
    // TODO: is this used?
    class TimeLimitException : public std::runtime_error {
    public:
        TimeLimitException() : std::runtime_error("Time limit exceeded") {
        }
    };
}
