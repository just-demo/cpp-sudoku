#pragma once

#include <chrono>

namespace sudoku {
    class RunGenerator {
    public:
        static void generateMany();

    private:
        static constexpr std::chrono::seconds GENERATOR_TIMEOUT{3};
        // static constexpr std::chrono::minutes REDUCER_TIMEOUT{1};
        static constexpr std::chrono::seconds REDUCER_TIMEOUT{1};
    };
}
