#include "value.hpp"
#include "cell.hpp"
#include <functional>
#include <algorithm>

Value::Value(std::vector<Value*>& pending_values, int target_open_cells_count, int value)
    : pending_values_(pending_values), target_open_cells_count_(target_open_cells_count), value_(value) {}

void Value::addCandidateCells(const std::vector<Cell*>& cells) {
    auto rowGroups = groupBy(cells, [](const Cell* cell) { return cell->getRow(); });
    auto colGroups = groupBy(cells, [](const Cell* cell) { return cell->getCol(); });
    auto boxGroups = groupBy(cells, [](const Cell* cell) { return cell->getBox(); });
    
    candidate_cell_groups_.insert(candidate_cell_groups_.end(), rowGroups.begin(), rowGroups.end());
    candidate_cell_groups_.insert(candidate_cell_groups_.end(), colGroups.begin(), colGroups.end());
    candidate_cell_groups_.insert(candidate_cell_groups_.end(), boxGroups.begin(), boxGroups.end());
}

std::vector<std::vector<Cell*>> Value::groupBy(const std::vector<Cell*>& items, 
                                              std::function<int(const Cell*)> groupKeyFunc) const {
    std::unordered_map<int, std::vector<Cell*>> groups;
    for (Cell* item : items) {
        groups[groupKeyFunc(item)].push_back(item);
    }
    
    std::vector<std::vector<Cell*>> result;
    for (const auto& pair : groups) {
        result.push_back(pair.second);
    }
    return result;
}

void Value::removeCandidateCell(Cell* cell) {
    for (auto it = candidate_cell_groups_.begin(); it != candidate_cell_groups_.end();) {
        auto& cells = *it;
        auto cellIt = std::find(cells.begin(), cells.end(), cell);
        if (cellIt != cells.end()) {
            cells.erase(cellIt);
            if (cells.empty()) {
                it = candidate_cell_groups_.erase(it);
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }
}

void Value::openCandidateCell(Cell* cell) {
    removeCandidateCell(cell);
    open_cells_.push_back(cell);
    if (open_cells_.size() == static_cast<size_t>(target_open_cells_count_)) {
        auto it = std::find(pending_values_.begin(), pending_values_.end(), this);
        if (it != pending_values_.end()) {
            pending_values_.erase(it);
        }
    }
}

std::vector<Cell*> Value::getCandidateCells() const {
    if (candidate_cell_groups_.empty()) {
        return {};
    }
    
    auto minGroup = std::min_element(candidate_cell_groups_.begin(), candidate_cell_groups_.end(),
        [](const std::vector<Cell*>& a, const std::vector<Cell*>& b) {
            return a.size() < b.size();
        });
    
    return *minGroup;
}

bool Value::hasCandidateCells() const {
    return !candidate_cell_groups_.empty();
}

size_t Value::countCandidateCells() const {
    if (candidate_cell_groups_.empty()) {
        return 0;
    }
    
    auto minGroup = std::min_element(candidate_cell_groups_.begin(), candidate_cell_groups_.end(),
        [](const std::vector<Cell*>& a, const std::vector<Cell*>& b) {
            return a.size() < b.size();
        });
    
    return minGroup->size();
}

bool Value::tryOpenSingleCandidateCell() {
    std::vector<Cell*> cells = getCandidateCells();
    if (cells.size() == 1) {
        openCandidateCell(cells[0]);
        return true;
    }
    return false;
}
