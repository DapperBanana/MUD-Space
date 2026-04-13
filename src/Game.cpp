#include "Game.h"
#include "Room.h"
#include <iostream>
#include <thread>
#include <chrono>

Game::Game()
{
    // Initialize the starting room
    Room* startRoom = new Room("The Void", "An empty, dark space. Stars glimmer distantly.");
    rooms_["void"] = startRoom;
    std::cout << "Initialized room: " << startRoom->name << std::endl;
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
