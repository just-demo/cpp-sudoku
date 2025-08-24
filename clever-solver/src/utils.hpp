#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <optional>

namespace sudoku {

class Utils {
public:
    static constexpr const char* EMPTY_VALUE = ".";
    
    static std::string asString(const std::vector<std::vector<std::optional<int>>>& matrix) {
        std::ostringstream oss;
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                if (j > 0) oss << " ";
                if (matrix[i][j].has_value()) {
                    oss << matrix[i][j].value();
                } else {
                    oss << EMPTY_VALUE;
                }
            }
            if (i < matrix.size() - 1) oss << "\n";
        }
        return oss.str();
    }
    
    static std::vector<std::vector<std::optional<int>>> parseSimpleString(const std::string& flat) {
        int size = static_cast<int>(std::sqrt(flat.length()));
        std::vector<std::vector<std::optional<int>>> matrix(size, std::vector<std::optional<int>>(size));
        
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                char value = flat[row * size + col];
                if (value == '.' || value == '0') {
                    matrix[row][col] = std::nullopt;
                } else {
                    matrix[row][col] = value - '0';
                }
            }
        }
        return matrix;
    }
};

} // namespace sudoku
