//
// Created by Bobby Lucero on 1/8/23.
//

#include "Headers/GameSolver.h"
#include "Headers/Math.h"
#include "Headers/HelperFunctions.h"

void GameSolver::printBoard(int *board) {
    for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i) {
        std::cout << board[i] << ", ";
        if((i + 1) % BOARD_WIDTH == 0){
            std::cout << "\n";
        }
    }

    std::cout << std::endl;
}

GameSolver::GameSolver(SymbolFactory *factory) {
    this->symbolFactory = factory;
}

int *GameSolver::Solve(double multiplier) {

    Math::setSeed(time(nullptr));

    int* board = new int[BOARD_WIDTH * BOARD_HEIGHT];

    for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i) {
        board[i] = -1;
    }

    int symID = -1;
    for (int i = 0; i < this->symbolFactory->Symbols.size(); ++i) {
        if(this->symbolFactory->Symbols[i].multiplier == multiplier){
            symID = this->symbolFactory->Symbols[i].id;
            break;
        }
    }

    if(symID == -1){
        throw std::runtime_error("Cannot solve board for multiplier: " + std::to_string(multiplier));
    }

    int selectedWinline = Math::random(0, this->winLines.lines.size() - 1);
    if(symID != -1) {
        for (int winlineIndex: this->winLines.lines[selectedWinline]) {
            board[winlineIndex] = symID;
        }
    }

    bool solutionFound = false;

    int tries = GameSolver::NumTries;

    while(!solutionFound && tries > 0) {
        for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i) {
            if(!HelperFunctions<int>::Contains(this->winLines.lines[selectedWinline], i)){ //if this spot is not on a selectedWinline
                board[i] = this->symbolFactory->GetWeightedSymbol();
            }
        }

        bool boardInvalid = false;
        for (int i = 0; i < this->winLines.lines.size(); ++i) {
            if(i != selectedWinline){
                int symbolIDCheck = board[this->winLines.lines[i][0]];

                bool winLineHasWin = true;
                for (int j = 1; j < this->winLines.lines[i].size(); ++j) {
                    if(board[this->winLines.lines[i][j]] != symbolIDCheck) {
                        winLineHasWin = false;
                        break; //if any of them are different from the first symbol on the winline, no need to check the rest.
                    }
                }
                if(winLineHasWin){
                    std::cout << "Winline " << std::to_string(i) << " has unintended win." << std::endl;
                    boardInvalid = true;
                }
            }
        }

        if(!boardInvalid){
            solutionFound = true;
        }else{
            tries--;
        }

    }

    if(tries == 0){
        throw std::runtime_error("Failed to solve board for multiplier: " + std::to_string((int)multiplier) + "x.");
    }

    return board;
}

GameSolver::~GameSolver() {
    delete this->symbolFactory;
}

WinLines::WinLines() {
    lines.push_back(std::vector<int>{0,1,2});
    lines.push_back(std::vector<int>{3,4,5});
    lines.push_back(std::vector<int>{6,7,8});
    lines.push_back(std::vector<int>{0,4,8});
    lines.push_back(std::vector<int>{6,4,2});
}
