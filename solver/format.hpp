#pragma once
#include <vector>
#include <string>
#include <cmath>

// Convert 2D string representation to Sudoku grid
std::vector<std::vector<int>> sudokuFrom2DString(const std::string& str);

// Convert Sudoku grid to 2D string representation
std::string sudokuTo2DString(const std::vector<std::vector<int>>& sudoku);

// Convert single character to integer (0 for non-digit)
int cellFromString(const std::string& str);

// Convert 1D string representation to Sudoku grid
std::vector<std::vector<int>> sudokuFrom1DString(const std::string& str);
