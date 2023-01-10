//
// Created by Bobby Lucero on 1/8/23.
//

#include "../Headers/GameSolver.h"
#include "../Headers/Math.h"
#include "../Headers/HelperFunctions.h"
#include "../Headers/WinInfo.h"

void GameSolver::printBoard(int *board) {

    WinInfo winInfo(board, this->winLines, this->symbolFactory);

    for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i) {
        bool onWinLine = false;

        for (int k = 0; k < winInfo.WinningLines.size(); ++k) {
            if(HelperFunctions<int>::Contains(winLines.lines[winInfo.WinningLines[k]], i)){
                onWinLine = true;
            }
        }

        std::cout << (onWinLine ? gold : normal) << board[i] << normal << ", ";
        if((i + 1) % BOARD_WIDTH == 0){
            std::cout << "\n";
        }
    }

    std::cout << std::endl << green << "Board value: " << gold << winInfo.BoardValue << normal << std::endl;
}

GameSolver::GameSolver(SymbolFactory *factory) {
    this->symbolFactory = factory;
}

int* GameSolver::Solve(double multiplier, int seed) {

    if(seed != -1){
        Math::setSeed(seed);
    }else{
        Math::setSeed(time(nullptr));
    }

    int* board = new int[BOARD_WIDTH * BOARD_HEIGHT];

    bool canSplitWithSingleSymbol = false;
    bool canSplitWithMultipleSymbols = false;
    std::vector<int> selectedWinlineIndices;
    int sym;

    if(multiplier != 0) {
        //Split with single symbol test
        std::vector<std::pair<int, int>> potentialSymbols; //<symbolID, winlinesNeeded>

        for (auto sym: this->symbolFactory->Symbols) {

            if (sym.multiplier > multiplier) break;

            int winlinesNeeded = (int) (multiplier / sym.multiplier);

            if (((int) multiplier % (int) sym.multiplier == 0) && winlinesNeeded <= 5) {
                potentialSymbols.emplace_back(std::pair<int, int>(sym.id, winlinesNeeded));
                canSplitWithSingleSymbol = true;
            }
        }
        int idx = Math::random(0, potentialSymbols.size() - 1);
        sym = potentialSymbols[idx].first;
        int selectedWinlineCount = potentialSymbols[idx].second;
        //////////


        //Split with multiple symbols test

        //////////

        if (canSplitWithSingleSymbol) {
            switch (selectedWinlineCount) {
                case 1:
                    selectedWinlineIndices.emplace_back(Math::random(0, this->winLines.lines.size() - 1));
                    break;
                case 2:
                    for (int i = 0; i < 2; ++i) {
                        int choice;
                        do {
                            choice = Math::random(0, this->winLines.lines.size() - 1);
                        } while (HelperFunctions<int>::Contains(selectedWinlineIndices, choice));
                        selectedWinlineIndices.emplace_back(choice);
                    }
                    break;
                case 3:
                    if (Math::random(0, 10) <=
                        5) { //50% chance to do two diagonal, one horizontal, OR two horizontal, one diagonal
                        selectedWinlineIndices.emplace_back(3); //diagonal
                        selectedWinlineIndices.emplace_back(4); //diagonal
                        selectedWinlineIndices.emplace_back(Math::random(0, 2)); //random horizontal
                    } else { //TODO: random horizontal winlines can't be top or bottom on same board or else diagonal makes an extra winline
                        /*
                         * Board value: 12
                             2, 2,  2,
                            -1, 2, -1,
                             2, 2,  2,

                         */
                        selectedWinlineIndices.emplace_back(Math::random(3, 4)); //random diagonal
                        int choice;
                        for (int i = 0; i < 2; ++i) {
                            int choice;
                            do {
                                choice = Math::random(0, 2); //pick a random horizontal
                            } while (HelperFunctions<int>::Contains(selectedWinlineIndices, choice));
                            selectedWinlineIndices.emplace_back(choice);
                        }
                    }
                    break;
                case 4: //two diagonal and two random horizontal
                    selectedWinlineIndices.emplace_back(3);
                    selectedWinlineIndices.emplace_back(4);
                    for (int i = 0; i < 2; ++i) {
                        int choice;
                        do {
                            choice = Math::random(0, 2); //pick a random horizontal
                        } while (HelperFunctions<int>::Contains(selectedWinlineIndices, choice));
                        selectedWinlineIndices.emplace_back(choice);
                    }
                    break;
                case 5:
                    for (int i = 0; i < 5; ++i) {
                        selectedWinlineIndices.emplace_back(i);
                    }
                    break;

                default:
                    throw std::runtime_error("Invalid winline count");
            }
        }
    }

    //std::cout << "SymID: " << std::to_string(sym) << " Required winlines: " + std::to_string(selectedWinlineCount) << std::endl;

    bool solutionFound = false;

    int tries = GameSolver::NumTries;


    while(!solutionFound && tries > 0) {

        //Reset the board
        for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i) {
            board[i] = -1;
        }

        //Place the winline
        for (int i = 0; i < selectedWinlineIndices.size(); ++i) {
            for (int winlineIndex: this->winLines.lines[selectedWinlineIndices[i]]) {
                board[winlineIndex] = sym;
            }
        }

        printBoard(board);

        //fill in the rest of the symbols
        for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i) {
            if(board[i] == -1){ //if this spot is not on a selected Winline
                board[i] = this->symbolFactory->GetWeightedSymbol();
            }
        }

        bool boardInvalid = false;

        for (int i = 0; i < this->winLines.lines.size(); ++i) {

                if (!HelperFunctions<int>::Contains(selectedWinlineIndices, i) || multiplier == 0) {
                    int symbolIDCheck = board[this->winLines.lines[i][0]];

                    bool winLineHasWin = true;
                    for (int j = 1; j < this->winLines.lines[i].size(); ++j) {
                        if (board[this->winLines.lines[i][j]] != symbolIDCheck) {
                            winLineHasWin = false;
                            break; //if any of them are different from the first symbol on the winline, no need to check the rest.
                        }
                    }
                    if (winLineHasWin) {
                        //std::cout << "Winline " << std::to_string(i) << " has unintended win." << std::endl;

                        boardInvalid = true;
                    }
                }

        }

        if(!boardInvalid){
            solutionFound = true;
            std::cout << green << "Solution Found For " << std::to_string((int)multiplier) << "x" << normal << std::endl;

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
