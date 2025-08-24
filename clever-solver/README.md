# C++20 Sudoku Solver

This is a C++20 implementation of a Sudoku solver, migrated from the original Java version.

## Features

- Solves 9x9 Sudoku puzzles using constraint propagation and backtracking
- Handles multiple solution detection
- Exception handling for unsolvable puzzles
- Performance timing

## Building

### Prerequisites

- C++20 compatible compiler (GCC 10+, Clang 12+, or MSVC 2019+)

### Build Instructions

```bash
make
```

Or with CMake (if available):

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

Run the solver:

```bash
./sudoku-solver
```

The program will solve the hardcoded Sudoku puzzle and display the solution along with execution time.

## Project Structure

- `src/clever_solver.hpp/cpp` - Main solver implementation
- `src/utils.hpp` - Utility functions for parsing and formatting
- `src/exceptions.hpp` - Custom exception classes
- `src/main.cpp` - Main program entry point
- `Makefile` - Build configuration
- `CMakeLists.txt` - Alternative CMake build configuration

## Algorithm

The solver uses a constraint propagation approach:

1. **Initialization**: Creates cells and values with candidate relationships
2. **Constraint Propagation**: Removes impossible candidates based on Sudoku rules
3. **Single Candidate Resolution**: Places values when only one candidate remains
4. **Backtracking**: When no single candidates exist, makes educated guesses
5. **Multiple Solution Detection**: Throws exception if multiple solutions are found

## Performance

The C++ implementation should be significantly faster than the Java version due to:
- Direct memory management
- Reduced object allocation overhead
- Optimized data structures (unordered_sets, vectors)
- Compile-time optimizations
