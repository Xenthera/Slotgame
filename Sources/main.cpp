#include <iostream>
#include "../Headers/GameSolver.h"

int main() {
    GameSolver* gameSolver = new GameSolver(new SymbolFactory());

    //std::cout << "Enter a seed: ";
    //int seed;
    //std::cin >> seed;
    int* board = gameSolver->Solve(9, 9);
    gameSolver->printBoard(board);
    delete[] board;
    delete gameSolver;
}
