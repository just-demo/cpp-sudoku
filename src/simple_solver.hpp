#pragma once

#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include "cell.hpp"
#include "exceptions.hpp"
#include "utils.hpp"

namespace sudoku {

class SimpleSolver {
private:
    std::vector<std::vector<int>> solution_;
    std::list<Cell> pendingCells_;

    void open(const Cell& cell, int value);

public:
    explicit SimpleSolver(const std::vector<std::vector<int>>& initialValues);
    std::vector<std::vector<int>> solve();
};

} // namespace sudoku
