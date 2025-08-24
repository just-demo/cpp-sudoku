#include "cell.hpp"
#include "value.hpp"
#include <algorithm>

Cell::Cell(std::vector<Cell*>& pending_cells, int row, int col, int box)
    : pending_cells_(pending_cells), row_(row), col_(col), box_(box), value_(nullptr) {}

void Cell::addCandidateValues(const std::vector<Value*>& values) {
    candidate_values_.insert(candidate_values_.end(), values.begin(), values.end());
}

void Cell::openCandidateValue(Value* value) {
    value_ = value;
    
    // Remove this cell from all candidate values
    for (Value* val : candidate_values_) {
        val->removeCandidateCell(this);
    }
    candidate_values_.clear();
    
    // Open this cell in the value
    value->openCandidateCell(this);
    
    // Remove this cell from pending cells
    auto it = std::find(pending_cells_.begin(), pending_cells_.end(), this);
    if (it != pending_cells_.end()) {
        pending_cells_.erase(it);
    }
    
    // Remove this value from competitor cells
    for (Cell* cell : pending_cells_) {
        if (isCompetitor(cell)) {
            cell->removeCandidateValue(value);
        }
    }
}

bool Cell::isCompetitor(const Cell* cell) const {
    return row_ == cell->row_ || col_ == cell->col_ || box_ == cell->box_;
}

void Cell::removeCandidateValue(Value* value) {
    value->removeCandidateCell(this);
    auto it = std::find(candidate_values_.begin(), candidate_values_.end(), value);
    if (it != candidate_values_.end()) {
        candidate_values_.erase(it);
    }
}

bool Cell::hasCandidateValues() const {
    return !candidate_values_.empty();
}

size_t Cell::countCandidateValues() const {
    return candidate_values_.size();
}

bool Cell::tryOpenSingleCandidateValue() {
    if (candidate_values_.size() == 1) {
        openCandidateValue(candidate_values_[0]);
        return true;
    }
    return false;
}

std::vector<Value*> Cell::getCandidateValues() const {
    return candidate_values_;
}
