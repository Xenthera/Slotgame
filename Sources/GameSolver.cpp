//
// Created by Bobby Lucero on 1/8/23.
//

#include <unordered_set>
#include <set>
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
    std::vector<int> selectedWinlineIndices;
    std::vector<int> SymIDsForWinlines;
    if(multiplier != 0)
        SymIDsForWinlines = this->SolveNonZeroBoard(multiplier, selectedWinlineIndices);

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
                board[winlineIndex] = SymIDsForWinlines[i];
            }
        }

        //fill in the rest of the symbols randomly,
        for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i) {
            if(board[i] == -1){ //if this spot is not on a selected Winline
                board[i] = this->symbolFactory->GetWeightedSymbol();
            }
        }

        bool boardInvalid = false;

        //Check each winline and make sure it contains no more than two of the same symbols on all the losing winlines.
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

std::vector<int> GameSolver::SolveNonZeroBoard(double multiplier, std::vector<int>& selectedWinlineIndices) const{
    enum SplitTypes{ //Used to keep track if the mult will be split between a single symbol ID, or multiple symbol IDs. Single Symbol ID can also be "split" 1 way (IE a single win line board)
        Single,
        Multi
    };

    std::unordered_set<SplitTypes, std::hash<int>> availableSplitTypes;

    //=== Split with single symbol test ================================================================================
    std::vector<std::pair<int, int>> potentialSymbols; //<symbolID, winlinesNeeded>
    std::vector<int> symIDsForWinlines;

    for (auto sym: this->symbolFactory->Symbols) {

        if (sym.multiplier > multiplier) break;

        int winlinesNeeded = (int) (multiplier / sym.multiplier);

        if (((int) multiplier % (int) sym.multiplier == 0) && winlinesNeeded <= 5) {
            potentialSymbols.emplace_back(sym.id, winlinesNeeded);
            availableSplitTypes.insert(Single);
        }
    }
    //==================================================================================================================



    //=== Split with multiple symbols test =============================================================================
    std::vector<double> rndSplit;
    auto PossibleSplits = HelperFunctions<double>::split_number(multiplier, this->symbolFactory->MultList);

    if(!PossibleSplits.empty()) {
        rndSplit = PossibleSplits[Math::random(0, PossibleSplits.size() - 1)];
        availableSplitTypes.insert(Multi);
    }



    //==================================================================================================================

    if(availableSplitTypes.empty()) throw std::runtime_error("No way to solve for multiplier: " + std::to_string(multiplier));

    std::vector<SplitTypes> splitTypesVector{};

    std::unordered_set<SplitTypes, std::hash<int>>::iterator iter;

    for(iter = availableSplitTypes.begin(); iter != availableSplitTypes.end(); iter++){
        splitTypesVector.push_back(*iter);
    }

    SplitTypes choice = splitTypesVector[Math::random(0, splitTypesVector.size() - 1)];

    if (choice == Single) {

        int idx = Math::random(0, potentialSymbols.size() - 1);
        int sym = potentialSymbols[idx].first;
        int selectedWinlineCount = potentialSymbols[idx].second;

        switch (selectedWinlineCount) {
            case 1:
                selectedWinlineIndices.emplace_back(Math::random(0, this->winLines.lines.size() - 1));
                symIDsForWinlines.emplace_back(sym);
                break;
            case 2:
                for (int i = 0; i < 2; ++i) {
                    int choice;
                    do {
                        choice = Math::random(0, this->winLines.lines.size() - 1);
                    } while (HelperFunctions<int>::Contains(selectedWinlineIndices, choice));
                    selectedWinlineIndices.emplace_back(choice);
                    symIDsForWinlines.emplace_back(sym);
                }
                break;
            case 3:
                if (Math::random(0, 10) <=
                    5) { //50% chance to do two diagonal, one horizontal, OR two horizontal, one diagonal
                    selectedWinlineIndices.emplace_back(3); //diagonal
                    selectedWinlineIndices.emplace_back(4); //diagonal
                    selectedWinlineIndices.emplace_back(Math::random(0, 2)); //random horizontal
                } else {
                    selectedWinlineIndices.emplace_back(Math::random(3, 4)); //random diagonal
                    int choice = Math::random(0, 2); //pick a random horizontal
                    selectedWinlineIndices.emplace_back(choice);
                    if(choice == 0 || choice == 2){
                        selectedWinlineIndices.emplace_back(1);
                    }else{
                        if(Math::random(0,10) < 5){
                            selectedWinlineIndices.emplace_back(0);
                        }else{
                            selectedWinlineIndices.emplace_back(2);
                        }
                    }
                }
                for (int i = 0; i < 3; ++i) {
                    symIDsForWinlines.emplace_back(sym);
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
                for (int i = 0; i < 4; ++i) {
                    symIDsForWinlines.emplace_back(sym);
                }
                break;
            case 5:
                for (int i = 0; i < 5; ++i) {
                    selectedWinlineIndices.emplace_back(i);
                    symIDsForWinlines.emplace_back(sym);
                }
                break;

            default:
                throw std::runtime_error("Invalid winline count");
        }
    }
    else if(choice == Multi){
        for (int i = 0; i < rndSplit.size(); ++i) {

            int choice;
            do {
                choice = Math::random(0, 2);
            } while (HelperFunctions<int>::Contains(selectedWinlineIndices, choice));
            selectedWinlineIndices.emplace_back(choice); //get random unique winlines and add them to selectedWinlineIndices

            symIDsForWinlines.emplace_back(symbolFactory->GetSymbolIDFromMult(rndSplit[i])); //add the symbolIDs that will be put on the winlines above
        }
    }

    return symIDsForWinlines;
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
