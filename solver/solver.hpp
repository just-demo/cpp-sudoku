#pragma once
#include <vector>
#include <memory>
#include <cmath>
#include "cell.hpp"
#include "value.hpp"

class Solver {
public:
    explicit Solver(const std::vector<std::vector<int>>& initial_state);
    std::vector<std::vector<int>> solve();
    
private:
    int size_;
    std::vector<std::unique_ptr<Cell>> all_cells_;
    std::vector<Cell*> pending_cells_;
    std::vector<std::unique_ptr<Value>> all_values_;
    std::vector<Value*> pending_values_;
    
    void openNext();
    std::vector<std::vector<int>> copyState() const;
    std::vector<std::vector<int>> solveWithGuess(Cell* cell, Value* value);
};
