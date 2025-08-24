CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
TARGET = sudoku-solver
SOURCES = src/main.cpp src/clever_solver.cpp
HEADERS = src/clever_solver.hpp src/utils.hpp src/exceptions.hpp

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean
