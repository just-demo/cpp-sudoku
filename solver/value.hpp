#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>

// Forward declarations
class Cell;

class Value {
public:
    Value(std::vector<Value*>& pending_values, int target_open_cells_count, int value);
    
    void addCandidateCells(const std::vector<Cell*>& cells);
    void removeCandidateCell(Cell* cell);
    void openCandidateCell(Cell* cell);
    std::vector<Cell*> getCandidateCells() const;
    bool hasCandidateCells() const;
    size_t countCandidateCells() const;
    bool tryOpenSingleCandidateCell();
    
    // Getter
    int getValue() const { return value_; }
    
private:
    std::vector<Value*>& pending_values_;
    int target_open_cells_count_;
    int value_;
    std::vector<Cell*> open_cells_;
    std::vector<std::vector<Cell*>> candidate_cell_groups_;
    
    std::vector<std::vector<Cell*>> groupBy(const std::vector<Cell*>& items, 
                                           std::function<int(const Cell*)> groupKeyFunc) const;
};
