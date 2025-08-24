#include <iostream>
#include <chrono>
#include "simple_solver.hpp"
#include "utils.hpp"

int main() {
    std::string sudokuStr = ".......9......8.2.7.3.54.....52.................6....88....3..7.9....6..6...8...4";
    auto sudoku = sudoku::Utils::parseSimpleString(sudokuStr);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    try {
        auto solution = sudoku::SimpleSolver(sudoku).solve();
        std::cout << sudoku::Utils::asString(solution) << std::endl;
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Time: " << duration.count() << " ms" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
