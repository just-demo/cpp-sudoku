cmake_minimum_required(VERSION 3.20)
project(sudoku-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(src)

# Source files
set(SOURCES
        src/solver/Solver.cpp
        src/generator/Reducer.cpp
        src/generator/Generator.cpp
)

# Create library
add_library(sudoku-lib STATIC ${SOURCES})

# Create test executables
add_executable(solver-test test/solver/SolverTest.cpp)
target_link_libraries(solver-test sudoku-lib)

add_executable(reducer-test test/generator/ReducerTest.cpp)
target_link_libraries(reducer-test sudoku-lib)

# Create main executables
add_executable(run-generator src/main/RunGenerator.cpp)
target_link_libraries(run-generator sudoku-lib)

add_executable(run-solver src/main/RunSolver.cpp)
target_link_libraries(run-solver sudoku-lib)

# Enable testing
enable_testing()
add_test(NAME solver-test COMMAND solver-test)
add_test(NAME reducer-test COMMAND reducer-test)
add_test(NAME generator-test COMMAND generator-test)
