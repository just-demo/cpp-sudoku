#include "format.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

std::vector<std::vector<int>> sudokuFrom2DString(const std::string& str) {
    std::vector<std::vector<int>> result;
    std::istringstream iss(str);
    std::string line;
    
    while (std::getline(iss, line)) {
        if (line.empty()) continue;
        
        std::vector<int> row;
        std::istringstream lineStream(line);
        std::string cell;
        
        while (lineStream >> cell) {
            row.push_back(cellFromString(cell));
        }
        
        if (!row.empty()) {
            result.push_back(row);
        }
    }
    
    return result;
}

std::string sudokuTo2DString(const std::vector<std::vector<int>>& sudoku) {
    std::ostringstream oss;
    
    for (size_t i = 0; i < sudoku.size(); ++i) {
        for (size_t j = 0; j < sudoku[i].size(); ++j) {
            if (j > 0) oss << " ";
            if (sudoku[i][j] == 0) {
                oss << ".";
            } else {
                oss << sudoku[i][j];
            }
        }
        if (i < sudoku.size() - 1) {
            oss << "\n";
        }
    }
    
    return oss.str();
}

int cellFromString(const std::string& str) {
    if (str.empty()) return 0;
    
    // Check if the string represents a digit
    if (std::all_of(str.begin(), str.end(), ::isdigit)) {
        return std::stoi(str);
    }
    
    return 0;
}

std::vector<std::vector<int>> sudokuFrom1DString(const std::string& str) {
    int size = static_cast<int>(std::sqrt(str.length()));
    std::vector<std::vector<int>> result(size, std::vector<int>(size));
    
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            std::string cellStr(1, str[row * size + col]);
            result[row][col] = cellFromString(cellStr);
        }
    }
    
    return result;
}
