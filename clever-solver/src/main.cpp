#include <iostream>
#include <chrono>
#include "clever_solver.hpp"
#include "utils.hpp"

int main() {
    std::string sudokuStr = ".......9......8.2.7.3.54.....52.................6....88....3..7.9....6..6...8...4";
    
    auto start = std::chrono::high_resolution_clock::now();
    
    try {
        auto sudoku = sudoku::Utils::parseSimpleString(sudokuStr);
        sudoku::CleverSolver solver(sudoku);
        auto solution = solver.solve();
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << sudoku::Utils::asString(solution) << std::endl;
        std::cout << "Time: " << duration.count() << " ms" << std::endl;
        
    } catch (const sudoku::MultipleSolutionsException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const sudoku::NoSolutionException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const sudoku::TimeLimitException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
