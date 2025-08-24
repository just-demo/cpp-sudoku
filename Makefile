CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O3
INCLUDES = -Isrc
SOURCES = src/simple_solver.cpp src/test_speed.cpp
TARGET = sudoku-solver

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

run: $(TARGET)
	./$(TARGET)
