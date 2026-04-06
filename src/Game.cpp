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
        std::cout << "Game tick" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
