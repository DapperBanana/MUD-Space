#include "Game.h"
#include "Room.h"
#include <iostream>
#include <thread>
#include <chrono>

Game::Game()
{
    init();
}

void Game::init()
{
    // Initialize the starting room
    Room* startRoom = new Room("The Void", "An empty, dark space. Stars glimmer distantly.");
    rooms_["void"] = startRoom;
    std::cout << "Initialized room: " << startRoom->name << std::endl;

    // Create a second room
    Room* secondRoom = new Room("North Room", "A slightly less empty space. More stars.");
    rooms_["north"] = secondRoom;
    std::cout << "Initialized room: " << secondRoom->name << std::endl;

    // Connect the rooms
    startRoom->exits["north"] = secondRoom;
    secondRoom->exits["south"] = startRoom;


}

void Game::run()
{
    running_ = true;

    while (running_)
    {
        std::cout << "Game tick" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate game tick
    }
}

void Game::stop()
{
    running_ = false;
}
