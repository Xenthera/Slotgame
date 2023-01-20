//
// Created by bobby on 1/14/23.
//
#include "../Headers/Game.h"

Game::Game(){
    console = new Console();
    gameSolver = new GameSolver(new SymbolFactory());
}
Game::~Game() {
    delete this->console;
    delete this->gameSolver;
}

bool Game::OnUserCreate() {
    ConsoleCaptureStdOut(true);
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    Clear(olc::VERY_DARK_GREY);

    if(GetKey(olc::Key::TAB).bPressed){
        ConsoleShow(olc::Key::TAB);
    }

    return true;
}

void Game::OnTextEntryComplete(const std::string& text) {
    std::cout << "[Console]: "<< text << std::endl;
}
bool Game::OnConsoleCommand(const std::string& text) {
    console->RunCommand(this, text);
}

void Game::SolveBoard() {
    int* board = this->gameSolver->Solve(5);
    this->gameSolver->printBoard(board, true);
    delete[] board;
}


