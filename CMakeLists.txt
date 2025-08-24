cmake_minimum_required(VERSION 3.16)
project(cpp-sudoku)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable optimizations for release builds
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Source files
set(SOURCES
    solver/main.cpp
    solver/solver.cpp
    solver/cell.cpp
    solver/value.cpp
    solver/format.cpp
    solver/errors.cpp
    solver/test_speed.cpp
)

# Header files
set(HEADERS
    solver/solver.hpp
    solver/cell.hpp
    solver/value.hpp
    solver/format.hpp
    solver/errors.hpp
)

# Create main executable
add_executable(sudoku_solver solver/main.cpp solver/solver.cpp solver/cell.cpp solver/value.cpp solver/format.cpp solver/errors.cpp)

# Create test_speed executable
add_executable(test_speed solver/test_speed.cpp solver/solver.cpp solver/cell.cpp solver/value.cpp solver/format.cpp solver/errors.cpp)

# Set compiler flags
target_compile_features(sudoku_solver PRIVATE cxx_std_20)
target_compile_features(test_speed PRIVATE cxx_std_20)

# Add include directories
target_include_directories(sudoku_solver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/solver)
target_include_directories(test_speed PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/solver)

# Link libraries (if needed)
# target_link_libraries(sudoku_solver PRIVATE some_library)
# target_link_libraries(test_speed PRIVATE some_library)

# Set output directories
set_target_properties(sudoku_solver PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(test_speed PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
