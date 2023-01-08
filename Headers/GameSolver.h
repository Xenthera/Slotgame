//
// Created by Bobby Lucero on 1/8/23.
//
#include "SymbolFactory.h"
#include <algorithm>

#ifndef CPPSANDBOX_GAMESOLVER_H
#define CPPSANDBOX_GAMESOLVER_H

struct WinLines{
    std::vector<std::vector<int>> lines;
    WinLines();
};


class GameSolver {

public:
    static const int BOARD_WIDTH = 3;
    static const int BOARD_HEIGHT = 3;
    static void printBoard(int* board);
    static const int NumTries = 1000;

public:

    SymbolFactory* symbolFactory;
    WinLines winLines;

    GameSolver(SymbolFactory* factory);
    ~GameSolver();
    int* Solve(double multiplier);

private:

};


#endif //CPPSANDBOX_GAMESOLVER_H
