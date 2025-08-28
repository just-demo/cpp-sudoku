#pragma once

namespace sudoku {
    class RunReducer {
    public:
        static void reduceFailedByGeneratorTimeout();

        static void copyReducedToReady();
    };
}
