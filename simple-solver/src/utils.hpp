#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

namespace sudoku {

class Utils {
private:
    static constexpr const char* EMPTY_VALUE = ".";

public:
    static std::string asString(const std::vector<std::vector<int>>& matrix) {
        std::ostringstream oss;
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                if (j > 0) oss << " ";
                if (matrix[i][j] == 0) {
                    oss << EMPTY_VALUE;
                } else {
                    oss << matrix[i][j];
                }
            }
            if (i < matrix.size() - 1) oss << "\n";
        }
        return oss.str();
    }

    static std::vector<std::vector<int>> copy(const std::vector<std::vector<int>>& source) {
        return source; // std::vector has copy constructor
    }

    static std::vector<std::vector<int>> parseSimpleString(const std::string& flat) {
        int size = static_cast<int>(std::sqrt(flat.length()));
        std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
        
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                char value = flat[row * size + col];
                if (value == '.') {
                    matrix[row][col] = 0; // 0 represents empty cell
                } else {
                    matrix[row][col] = value - '0'; // Convert char to int
                }
            }
        }
        return matrix;
    }
};

} // namespace sudoku
