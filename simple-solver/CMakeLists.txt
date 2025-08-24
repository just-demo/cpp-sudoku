cmake_minimum_required(VERSION 3.20)
project(sudoku-solver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
        src/simple_solver.cpp
        src/test_speed.cpp
)

# Create executable
add_executable(sudoku-solver ${SOURCES})

# Include directories
target_include_directories(sudoku-solver PRIVATE src)

# Set compiler flags for optimization
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(sudoku-solver PRIVATE -O3)
endif()

# Enable warnings
target_compile_options(sudoku-solver PRIVATE -Wall -Wextra -Wpedantic)
