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
    static const int NumTries = 1000;

    //colors
    static inline const std::string green = "\033[92m";
    static inline const std::string gold = "\033[93m";
    static inline const std::string normal = "\033[39m";

public:

    SymbolFactory* symbolFactory;
    WinLines winLines;

    GameSolver(SymbolFactory* factory);
    ~GameSolver();
    int *Solve(double multiplier, int i = -1);
    void printBoard(int* board);
private:
    std::vector<int> SolveNonZeroBoard(double multiplier, std::vector<int> & selectedWinlineIndices) const;


private:

};


#endif //CPPSANDBOX_GAMESOLVER_H
