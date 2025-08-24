#include "solver.hpp"
#include "cell.hpp"
#include "value.hpp"
#include "errors.hpp"
#include <algorithm>
#include <stdexcept>

Solver::Solver(const std::vector<std::vector<int>>& initial_state) : size_(initial_state.size()) {
    int box_size = static_cast<int>(std::sqrt(size_));
    
    // Create all values
    for (int i = 0; i < size_; ++i) {
        all_values_.push_back(std::make_unique<Value>(pending_values_, size_, i + 1));
        pending_values_.push_back(all_values_.back().get());
    }
    
    // Create all cells and track open cells
    std::vector<std::pair<Cell*, Value*>> open_cells;
    
    for (int row = 0; row < size_; ++row) {
        for (int col = 0; col < size_; ++col) {
            int box = box_size * (row / box_size) + col / box_size;
            all_cells_.push_back(std::make_unique<Cell>(pending_cells_, row, col, box));
            pending_cells_.push_back(all_cells_.back().get());
            
            int value = initial_state[row][col];
            if (value != 0) {
                open_cells.emplace_back(all_cells_.back().get(), all_values_[value - 1].get());
            }
        }
    }
    
    // Add candidate values to all cells
    for (Cell* cell : pending_cells_) {
        cell->addCandidateValues(pending_values_);
    }
    
    // Add candidate cells to all values
    for (Value* value : pending_values_) {
        value->addCandidateCells(pending_cells_);
    }
    
    // Open cells that already have values
    for (const auto& [cell, value] : open_cells) {
        cell->openCandidateValue(value);
    }
}

std::vector<std::vector<int>> Solver::solve() {
    while (!pending_cells_.empty()) {
        try {
            openNext();
        } catch (const CannotOpenWithoutGuessingException& e) {
            return solveWithGuess(e.getCell(), e.getValue());
        }
    }
    return copyState();
}

std::vector<std::vector<int>> Solver::copyState() const {
    std::vector<std::vector<int>> state(size_, std::vector<int>(size_, 0));
    for (const auto& cell : all_cells_) {
        if (cell->getValue()) {
            state[cell->getRow()][cell->getCol()] = cell->getValue()->getValue();
        }
    }
    return state;
}

void Solver::openNext() {
    if (pending_values_.empty()) {
        throw NoSolutionException();
    }
    
    // Find cell with minimum candidate values
    auto minCell = std::min_element(pending_cells_.begin(), pending_cells_.end(),
        [](const Cell* a, const Cell* b) {
            return a->countCandidateValues() < b->countCandidateValues();
        });
    
    if ((*minCell)->tryOpenSingleCandidateValue()) {
        return;
    }
    
    // Find value with minimum candidate cells
    auto minValue = std::min_element(pending_values_.begin(), pending_values_.end(),
        [](const Value* a, const Value* b) {
            return a->countCandidateCells() < b->countCandidateCells();
        });
    
    if ((*minValue)->tryOpenSingleCandidateCell()) {
        return;
    }
    
    if ((*minCell)->hasCandidateValues() && (*minValue)->hasCandidateCells()) {
        throw CannotOpenWithoutGuessingException(*minCell, *minValue);
    }
    
    throw NoSolutionException();
}

std::vector<std::vector<int>> Solver::solveWithGuess(Cell* cell, Value* value) {
    std::vector<Cell*> guess_cells;
    std::vector<Value*> guess_values;
    
    if (cell->countCandidateValues() > value->countCandidateCells()) {
        guess_cells = value->getCandidateCells();
        guess_values = {value};
    } else {
        guess_cells = {cell};
        guess_values = cell->getCandidateValues();
    }
    
    std::vector<std::vector<std::vector<int>>> solutions;
    
    for (Cell* guess_cell : guess_cells) {
        for (Value* guess_value : guess_values) {
            std::vector<std::vector<int>> guess_state = copyState();
            guess_state[guess_cell->getRow()][guess_cell->getCol()] = guess_value->getValue();
            
            try {
                Solver guess_solver(guess_state);
                solutions.push_back(guess_solver.solve());
                if (solutions.size() > 1) {
                    throw MultipleSolutionsException();
                }
            } catch (const NoSolutionException&) {
                // Our guess did not work, let's try another one
            }
        }
    }
    
    if (solutions.empty()) {
        throw NoSolutionException();
    }
    
    return solutions[0];
}
