#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

namespace just::demo::util {
    class SudokuUtils {
        static constexpr const char *EMPTY_AS_STRING = ".";

    public:
        static std::string toString1D(const std::vector<std::vector<int> > &matrix) {
            std::string result;
            for (const auto &row: matrix) {
                for (int cell: row) {
                    result += cellToString(cell);
                }
            }
            return result;
        }

        static std::string toString2D(const std::vector<std::vector<int> > &matrix) {
            std::string result;
            for (size_t i = 0; i < matrix.size(); ++i) {
                if (i > 0) {
                    result += "\n";
                }
                for (size_t j = 0; j < matrix[i].size(); ++j) {
                    if (j > 0) {
                        result += " ";
                    }
                    result += cellToString(matrix[i][j]);
                }
            }
            return result;
        }

        static std::vector<std::vector<int> > fromString1D(const std::string &flat) {
            int size = static_cast<int>(std::sqrt(flat.length()));
            std::vector matrix(size, std::vector<int>(size));

            for (int row = 0; row < size; ++row) {
                for (int col = 0; col < size; ++col) {
                    std::string value(1, flat[row * size + col]);
                    matrix[row][col] = cellFromString(value);
                }
            }
            return matrix;
        }

        static std::vector<std::vector<int> > fromString2D(const std::string &file) {
            std::istringstream iss(file);
            std::string line;
            std::vector<std::vector<int> > matrix;

            while (std::getline(iss, line)) {
                if (!line.empty()) {
                    matrix.push_back(parseLine2D(line));
                }
            }
            return matrix;
        }

        static long countOpen(const std::vector<std::vector<int> > &matrix) {
            long count = 0;
            for (const auto &row: matrix) {
                count += std::count_if(row.begin(), row.end(), [](int v) { return v != 0; });
            }
            return count;
        }

        static std::vector<std::vector<int> > copy(const std::vector<std::vector<int> > &source) {
            return source; // vector copy constructor creates deep copy
        }

    private:
        static std::vector<int> parseLine2D(const std::string &line) {
            std::vector<int> result;
            std::istringstream stream(line);
            std::string cell;

            while (stream >> cell) {
                result.push_back(cellFromString(cell));
            }
            return result;
        }

        static int cellFromString(const std::string &cell) {
            return cell == EMPTY_AS_STRING ? 0 : std::stoi(cell);
        }

        static std::string cellToString(int cell) {
            return cell == 0 ? EMPTY_AS_STRING : std::to_string(cell);
        }
    };
}
