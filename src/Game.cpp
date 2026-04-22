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

void Game::player_joins_game(Player& player)
{
    player.currentRoom = rooms_["void"];
    std::cout << "Player " << player.name << " joined the game in room " << player.currentRoom->name << std::endl;
}