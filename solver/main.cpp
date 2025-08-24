#include "solver.hpp"
#include "format.hpp"
#include <iostream>
#include <chrono>
#include <string>

int main() {
    std::string sudoku1 = R"(
5 3 . . 7 . . . .
6 . . 1 9 5 . . .
. 9 8 . . . . 6 .
8 . . . 6 . . . 3
4 . . 8 . 3 . . 1
7 . . . 2 . . . 6
. 6 . . . . 2 8 .
. . . 4 1 9 . . 5
. . . . 8 . . 7 9
)";

    std::string sudoku2 = ".......9......8.2.7.3.54.....52.................6....88....3..7.9....6..6...8...4";
    
    // Use the same test case as in Python
    auto sudoku = sudokuFrom1DString(sudoku2);
    
    std::cout << "Initial Sudoku:" << std::endl;
    std::cout << sudokuTo2DString(sudoku) << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    Solver solver(sudoku);
    auto solution = solver.solve();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "Time: " << duration.count() / 1000000000.0 << " seconds" << std::endl;
    std::cout << "Solution:" << std::endl;
    std::cout << sudokuTo2DString(solution) << std::endl;
    
    return 0;
}
