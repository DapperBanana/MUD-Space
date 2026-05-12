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
    startRoom->items.emplace_back("Old Boot", "A worn leather boot.");
    rooms_["void"] = startRoom;
    std::cout << "Initialized room: " << startRoom->name << std::endl;

    // Create a second room
    Room* secondRoom = new Room("North Room", "A slightly less empty space. More stars.");
    secondRoom->items.emplace_back("Glimmering Dust", "Some shimmering space dust.");
    rooms_["north"] = secondRoom;
    std::cout << "Initialized room: " << secondRoom->name << std::endl;

    // Connect the rooms
    startRoom->exits["north"] = secondRoom;
    secondRoom->exits["south"] = startRoom;
}

void Game::run()
{
    while (true) {
        // Game logic here (e.g., update world state)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
