#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>

Game::Game()
{
}

void Game::run()
{
    running_ = true;

    while (running_)
    {
        //Add new player to the game
        //Player newPlayer = {"Test"};
        //players_[players_.size()+1] = newPlayer;

        std::cout << "Game tick" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
