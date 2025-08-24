#include "simple_solver.hpp"
#include <cmath>
#include <ranges>

namespace sudoku {

SimpleSolver::SimpleSolver(const std::vector<std::vector<int>>& initialValues) {
    int size = static_cast<int>(initialValues.size());
    int blockSize = static_cast<int>(std::sqrt(size));
    
    // Create set of all possible values (1 to size)
    std::set<int> values;
    for (int i = 1; i <= size; ++i) {
        values.insert(i);
    }

    solution_ = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
    std::map<Cell, int> openCells;
    
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            int block = blockSize * (row / blockSize) + col / blockSize;
            int value = initialValues[row][col];
            
            if (value != 0) {
                openCells[Cell(row, col, block, std::set<int>{})] = value;
            } else {
                pendingCells_.emplace_back(row, col, block, values);
            }
        }
    }

    // Open all initial cells
    for (const auto& [cell, value] : openCells) {
        open(cell, value);
    }
}

std::vector<std::vector<int>> SimpleSolver::solve() {
    while (!pendingCells_.empty()) {
        // Find cell with minimum candidates
        auto minCellIt = std::min_element(pendingCells_.begin(), pendingCells_.end(),
            [](const Cell& a, const Cell& b) {
                return a.countCandidates() < b.countCandidates();
            });
        
        Cell cell = *minCellIt;
        
        if (cell.countCandidates() == 1) {
            open(cell, cell.getCandidate());
        } else if (cell.countCandidates() > 1) {
            std::vector<std::vector<std::vector<int>>> solutions;
            
            for (int value : cell.getCandidates()) {
                std::vector<std::vector<int>> nextGuess = Utils::copy(solution_);
                nextGuess[cell.getRow()][cell.getCol()] = value;
                
                try {
                    solutions.push_back(SimpleSolver(nextGuess).solve());
                    if (solutions.size() > 1) {
                        throw MultipleSolutionsException();
                    }
                } catch (const NoSolutionException&) {
                    // Our guess did not work, let's try another one
                }
            }
            
            if (solutions.empty()) {
                throw NoSolutionException();
            }
            
            return solutions.front();
        } else {
            throw NoSolutionException();
        }
    }

    return solution_;
}

void SimpleSolver::open(const Cell& cell, int value) {
    solution_[cell.getRow()][cell.getCol()] = value;
    
    // Remove the cell from pending cells
    pendingCells_.remove_if([&cell](const Cell& c) {
        return c.getRow() == cell.getRow() && c.getCol() == cell.getCol();
    });
    
    // Remove the value from candidates of related cells
    for (auto& pendingCell : pendingCells_) {
        if (cell.isRelated(pendingCell)) {
            pendingCell.removeCandidate(value);
        }
    }
}

} // namespace sudoku
