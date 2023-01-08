#include <iostream>
#include "../Headers/GameSolver.h"

int main() {
    GameSolver* gameSolver = new GameSolver(new SymbolFactory());


    int* board = gameSolver->Solve(100);
    GameSolver::printBoard(board);
    delete[] board;
    delete gameSolver;
}
