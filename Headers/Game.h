//
// Created by bobby on 1/14/23.
//
#ifndef CPPSANDBOX_GAME_H
#define CPPSANDBOX_GAME_H
#include "Console.h"
#include "GameEngine/olcPixelGameEngine.h"
#include "GameSolver.h"

class Game : public olc::PixelGameEngine {
public:
    Console* console;
    GameSolver* gameSolver;

    Game();
    ~Game();
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    void OnTextEntryComplete(const std::string& text) override;
    bool OnConsoleCommand(const std::string& text) override;
    void SolveBoard();
};
#endif //CPPSANDBOX_GAME_H
