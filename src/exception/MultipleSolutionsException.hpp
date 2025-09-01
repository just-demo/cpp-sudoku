#pragma once

#include <stdexcept>

namespace just::demo::exception {
    class MultipleSolutionsException : public std::runtime_error {
    public:
        MultipleSolutionsException() : std::runtime_error("Multiple solutions found") {
        }
    };
}
