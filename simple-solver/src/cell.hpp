#pragma once

#include <set>
#include <cstdint>

namespace sudoku {

class Cell {
private:
    int row_;
    int col_;
    int block_;
    std::set<int> candidates_;

public:
    Cell(int row, int col, int block, const std::set<int>& candidates)
        : row_(row), col_(col), block_(block), candidates_(candidates) {}

    int getRow() const { return row_; }
    int getCol() const { return col_; }
    int getBlock() const { return block_; }
    const std::set<int>& getCandidates() const { return candidates_; }

    bool isRelated(const Cell& cell) const {
        return row_ == cell.row_ || col_ == cell.col_ || block_ == cell.block_;
    }

    void removeCandidate(int value) {
        candidates_.erase(value);
    }

    int countCandidates() const {
        return static_cast<int>(candidates_.size());
    }

    int getCandidate() const {
        return *candidates_.begin();
    }

    // Comparison operators for use in std::map
    bool operator<(const Cell& other) const {
        if (row_ != other.row_) return row_ < other.row_;
        if (col_ != other.col_) return col_ < other.col_;
        return block_ < other.block_;
    }

    bool operator==(const Cell& other) const {
        return row_ == other.row_ && col_ == other.col_ && block_ == other.block_;
    }
};

} // namespace sudoku
