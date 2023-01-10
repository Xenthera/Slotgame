#include <iostream>
#include "../Headers/GameSolver.h"
#include <chrono>

int main() {
    auto* gameSolver = new GameSolver(new SymbolFactory());

    std::cout << "Enter number of boards to  generate: ";
    int count;
    std::cin >> count;

    std::vector<int*> boards;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < count; ++i) {
        int* board = gameSolver->Solve(200, i);
        //boards.push_back(board);
        if(i == count - 1)
            gameSolver->printBoard(board);
        delete[] board;
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Boards vector size: " + std::to_string(boards.size()) << std::endl;

    double timeEnd = time(nullptr);

    std::cout << "Time taken: " << std::to_string(elapsed_time) << "ms" << std::endl;

    delete gameSolver;
}
