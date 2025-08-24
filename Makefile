CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O3
INCLUDES = -Isolver
SOURCES = solver/main.cpp solver/solver.cpp solver/cell.cpp solver/value.cpp solver/format.cpp solver/errors.cpp
TEST_SOURCES = solver/test_speed.cpp solver/solver.cpp solver/cell.cpp solver/value.cpp solver/format.cpp solver/errors.cpp
TARGET = sudoku_solver
TEST_TARGET = test_speed

.PHONY: all clean test

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(TEST_TARGET): $(TEST_SOURCES)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

# Individual object files for faster rebuilds
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
