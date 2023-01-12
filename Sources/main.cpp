#include <iostream>
#include "../Headers/GameSolver.h"
#include "../Headers/WinInfo.h"
#include "../Headers/HelperFunctions.h"
#include <chrono>
#include <unordered_set>



#define OLC_PGE_APPLICATION
#include "../Headers/GameEngine/olcPixelGameEngine.h"

//Possible mults: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 21, 22, 23, 24, 25, 26, 27, 28, 30, 31, 32, 33, 35, 40, 50, 51, 52, 53, 54, 55, 56, 57, 58, 60, 61, 62, 63, 65, 70, 71, 72, 73, 75, 80, 100, 103, 104, 105, 106, 107, 108, 111, 112, 113, 115, 121, 122, 123, 125, 130, 150, 151, 152, 153, 155, 160, 170, 200, 250, 300, 400, 500

class Game : public olc::PixelGameEngine{
public:
    Game(){
        sAppName = "Slot Machine Game";
    }

    bool OnUserCreate() override{
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override{
        return true;
    }
};

int main() {
    auto* gameSolver = new GameSolver(new SymbolFactory());

    //std::cout << "Enter number of boards to  generate: ";
    //int count;
    ///std::cin >> count;


    int* board = gameSolver->Solve(2);

    gameSolver->printBoard(board);

    WinInfo info(board, gameSolver->winLines, gameSolver->symbolFactory);

    std::cout << "Winning lines: " << std::endl;
    for (auto line : info.WinningLines) {
        std::cout << line << ", ";
    }
    std::cout << std::endl;


    delete[] board;

    delete gameSolver;


    Game theGame;
    if(theGame.Construct(256, 256, 4, 4)){
        theGame.Start();
    }
}

void calculatePossibleMults(GameSolver* gameSolver){
    std::vector<int> possibleMults;
    for (int i = 0; i < 1000; ++i) {
        try {
            int *board = gameSolver->Solve(i);
            possibleMults.push_back(i);
        }catch(...){

        }
    }
    std::cout << "Possible Mults: ";
    for (int mult : possibleMults) {
        std::cout << mult << ", ";
    }
    std::cout << std::endl;
}
