#pragma once
#include <vector>
#include <algorithm>

// Forward declarations
class Value;

class Cell {
public:
    Cell(std::vector<Cell*>& pending_cells, int row, int col, int box);
    
    void addCandidateValues(const std::vector<Value*>& values);
    void openCandidateValue(Value* value);
    bool isCompetitor(const Cell* cell) const;
    void removeCandidateValue(Value* value);
    bool hasCandidateValues() const;
    size_t countCandidateValues() const;
    bool tryOpenSingleCandidateValue();
    std::vector<Value*> getCandidateValues() const;
    
    // Getters
    int getRow() const { return row_; }
    int getCol() const { return col_; }
    int getBox() const { return box_; }
    Value* getValue() const { return value_; }
    
private:
    std::vector<Cell*>& pending_cells_;
    int row_;
    int col_;
    int box_;
    Value* value_;
    std::vector<Value*> candidate_values_;
};
