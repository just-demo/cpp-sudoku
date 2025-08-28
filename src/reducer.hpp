#pragma once

#include <vector>
#include <optional>
#include <unordered_map>
#include <random>

namespace sudoku {
    class Cell;
    class CleverSolver;

    class Reducer {
        std::mt19937 rng;
        bool interrupted = false;

    public:
        Reducer();

        std::vector<std::vector<std::optional<int> > > reduce(
            const std::vector<std::vector<std::optional<int> > > &initialValues);

        void interrupt();

    private:
        std::vector<std::vector<std::optional<int> > > reduce(
            const std::vector<std::vector<std::optional<int> > > &initialValues,
            const std::vector<Cell> &closeCandidates);
    };
}
