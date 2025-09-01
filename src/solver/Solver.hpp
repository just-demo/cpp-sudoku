#pragma once
#include <vector>
#include <memory>
#include <stdexcept>

namespace just::demo::solver {
    class Solver {
    public:
        explicit Solver(const std::vector<std::vector<int> > &initialValues);

        std::vector<std::vector<int> > solve();

    private:
        class Value;
        class Cell;

        class CannotOpenWithoutGuessingException : public std::runtime_error {
        public:
            Cell *cell;
            Value *value;

            CannotOpenWithoutGuessingException(Cell *c, Value *v)
                : std::runtime_error("Cannot open without guessing"), cell(c), value(v) {
            }
        };

        class Cell {
            Solver *solver;
            Value *value{nullptr};
            std::vector<Value *> candidates;

        public:
            int row, col, block;

            Cell(Solver *s, int r, int c, int b) : solver(s), row(r), col(c), block(b) {
            }

            void setCandidates(const std::vector<Value *> &values);

            void open(Value *value);

            bool isRelated(const Cell &other) const;

            void removeCandidate(Value *value);

            int countCandidates() const {
                return (int) candidates.size();
            }

            Value *getCandidate() const {
                return candidates.front();
            }

            std::vector<Value*>& getCandidates() {
                return candidates;
            }

            int getValue() const {
                return value ? value->val : 0;
            }
        };

        class Value {
            Solver *solver;
            std::vector<Cell *> cells;
            std::vector<std::vector<Cell *> > candidates;

        public:
            int val;
            explicit Value(Solver *s, int v) : solver(s), val(v) {
            }

            void setCandidates(const std::vector<Cell *> &cells);

            void removeCandidate(Cell *c);

            void open(Cell *c);

            int countCandidates() const;

            Cell *getCandidate() const;

            std::vector<Cell *> getCandidates() const;
        };

        int size;
        std::vector<std::unique_ptr<Cell> > allCells;
        std::vector<Cell *> pendingCells;
        std::vector<std::unique_ptr<Value> > allValues;
        std::vector<Value *> pendingValues;

        void openNext();

        std::vector<std::vector<int> > solveWithGuess(Cell *cell, Value *value);

        std::vector<std::vector<int> > copyState() const;
    };
}
