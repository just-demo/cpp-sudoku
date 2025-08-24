cmake_minimum_required(VERSION 3.20)
project(sudoku-solver VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Add executable
add_executable(sudoku-solver src/main.cpp)

# Include directories
target_include_directories(sudoku-solver PRIVATE src)
