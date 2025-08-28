#pragma once

#include <vector>
#include <unordered_set>
#include <optional>
#include <random>

namespace sudoku {
    class CleverSolver;

    class Generator {
        int size;
        int complexityLowerLimit;
        int blockSize;
        std::unordered_set<int> values;
        std::mt19937 rng;
        bool interrupted = false;

    public:
        Generator(int size);

        Generator(int size, int complexityLowerLimit);

        std::vector<std::vector<std::optional<int> > > generate();

        void interrupt();

    private:
        std::vector<std::vector<std::optional<int> > > generate(
            const std::vector<std::vector<std::optional<int> > > &initialValues);
    };
}
