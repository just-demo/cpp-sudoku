#include "Solver.hpp"

#include <map>

#include "exception/MultipleSolutionsException.hpp"
#include "exception/NoSolutionException.hpp"

using namespace just::demo::exception;

namespace just::demo::solver {
    Solver::Solver(const std::vector<std::vector<int> > &initialValues) {
        size = (int) initialValues.size();
        int blockSize = (int) std::sqrt(size);

        for (int i = 1; i <= size; ++i) {
            allValues.push_back(std::make_unique<Value>(this, i));
        }

        std::map<Cell *, Value *> openCells;

        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                int block = blockSize * (row / blockSize) + col / blockSize;
                allCells.push_back(std::make_unique<Cell>(this, row, col, block));
                int value = initialValues[row][col];
                if (value != 0) {
                    openCells[allCells.back().get()] = allValues[value - 1].get();
                }
            }
        }

        for (auto &c: allCells) {
            pendingCells.push_back(c.get());
        }

        for (auto &v: allValues) {
            pendingValues.push_back(v.get());
        }

        for (auto &c: pendingCells) {
            c->setCandidates(pendingValues);
        }

        for (auto &v: pendingValues) {
            v->setCandidates(pendingCells);
        }

        for (auto &[c, v]: openCells) {
            c->open(v);
        }
    }

    std::vector<std::vector<int> > Solver::solve() {
        // TODO: implement interrupting
        while (!pendingCells.empty()) {
            try {
                openNext();
            } catch (CannotOpenWithoutGuessingException &e) {
                return solveWithGuess(e.cell, e.value);
            }
        }
        return copyState();
    }

    void Solver::openNext() {
        if (pendingValues.empty()) {
            throw NoSolutionException();
        }

        auto cellIt = std::ranges::min_element(pendingCells, [](Cell *a, Cell *b) {
            return a->countCandidates() < b->countCandidates();
        });
        Cell *cell = *cellIt;
        if (cell->countCandidates() == 1) {
            cell->open(cell->getCandidate());
            return;
        }

        auto valIt = std::ranges::min_element(pendingValues, [](Value *a, Value *b) {
            return a->countCandidates() < b->countCandidates();
        });
        Value *value = *valIt;
        if (value->countCandidates() == 1) {
            value->getCandidate()->open(value);
            return;
        }

        if (cell->countCandidates() == 0 || value->countCandidates() == 0) {
            throw NoSolutionException();
        }

        throw CannotOpenWithoutGuessingException(cell, value);
    }

    std::vector<std::vector<int> > Solver::solveWithGuess(Cell *cell, Value *value) {
        std::vector<Cell *> guessCells;
        std::vector<Value *> guessValues;
        if (cell->countCandidates() <= value->countCandidates()) {
            guessCells = {cell};
            guessValues = cell->getCandidates();
        } else {
            guessCells = value->getCandidates();
            guessValues = {value};
        }

        std::vector<std::vector<std::vector<int> > > solutions;
        for (auto *guessCell: guessCells) {
            for (auto *guessValue: guessValues) {
                auto nextGuess = copyState();
                nextGuess[guessCell->row][guessCell->col] = guessValue->val;
                try {
                    Solver s(nextGuess);
                    solutions.push_back(s.solve());
                    if (solutions.size() > 1) {
                        throw MultipleSolutionsException();
                    }
                } catch (NoSolutionException &) {
                    // Our guess did not work, let's try another one
                }
            }
        }

        if (solutions.empty()) {
            throw NoSolutionException();
        }

        return solutions.front();
    }

    std::vector<std::vector<int> > Solver::copyState() const {
        std::vector state(size, std::vector(size, 0));
        for (auto &cell: allCells) {
            state[cell->row][cell->col] = cell->getValue();
        }
        return state;
    }

    void Solver::Cell::setCandidates(const std::vector<Value *> &values) {
        candidates = values;
    }

    void Solver::Cell::open(Value *v) {
        value = v;
        for (auto *cv: candidates) {
            cv->removeCandidate(this);
        }

        candidates.clear();
        v->open(this);
        std::erase(solver->pendingCells, this);
        for (auto *pc: solver->pendingCells) {
            if (isRelated(*pc)) {
                pc->removeCandidate(v);
            }
        }
    }

    bool Solver::Cell::isRelated(const Cell &c) const {
        return row == c.row || col == c.col || block == c.block;
    }

    void Solver::Cell::removeCandidate(Value *v) {
        v->removeCandidate(this);
        std::erase(candidates, v);
    }

    void Solver::Value::setCandidates(const std::vector<Cell *> &cells) {
        auto groupBy = [](auto keyExtractor, const std::vector<Cell *> &cells) {
            std::map<int, std::vector<Cell *> > groups;
            for (auto *c: cells) groups[keyExtractor(c)].push_back(c);
            std::vector<std::vector<Cell *> > res;
            for (auto &[_, group]: groups) res.push_back(group);
            return res;
        };

        auto rowGroups = groupBy([](Cell *c) { return c->row; }, cells);
        auto colGroups = groupBy([](Cell *c) { return c->col; }, cells);
        auto blockGroups = groupBy([](Cell *c) { return c->block; }, cells);

        candidates.insert(candidates.end(), rowGroups.begin(), rowGroups.end());
        candidates.insert(candidates.end(), colGroups.begin(), colGroups.end());
        candidates.insert(candidates.end(), blockGroups.begin(), blockGroups.end());
    }

    void Solver::Value::removeCandidate(Cell *c) {
        for (auto &group: candidates) {
            std::erase(group, c);
        }
        std::erase_if(candidates, [](const auto &group) { return group.empty(); });
    }

    void Solver::Value::open(Cell *c) {
        removeCandidate(c);
        cells.push_back(c);
        if (static_cast<int>(cells.size()) == solver->size) {
            std::erase(solver->pendingValues, this);
        }
    }

    int Solver::Value::countCandidates() const {
        int minSize = INT_MAX;
        for (auto &group: candidates) {
            minSize = std::min(minSize, static_cast<int>(group.size()));
        }
        return minSize == INT_MAX ? 0 : minSize;
    }

    Solver::Cell *Solver::Value::getCandidate() const {
        return getCandidates().front();
    }

    std::vector<Solver::Cell *> Solver::Value::getCandidates() const {
        auto it = std::ranges::min_element(candidates,
                                           [](const auto &a, const auto &b) { return a.size() < b.size(); });
        return it == candidates.end() ? std::vector<Cell *>{} : *it;
    }
}
