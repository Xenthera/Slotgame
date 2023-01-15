//
// Created by bobby on 1/14/23.
//
#ifndef CPPSANDBOX_GAME_H
#define CPPSANDBOX_GAME_H
#include "Console.h"
#include "GameEngine/olcPixelGameEngine.h"

class Game : public olc::PixelGameEngine {
public:
    Console console;

    Game(){
        console = Console();
    }

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    void OnTextEntryComplete(const std::string& text) override;
    bool OnConsoleCommand(const std::string& text) override;
};
#endif //CPPSANDBOX_GAME_H
