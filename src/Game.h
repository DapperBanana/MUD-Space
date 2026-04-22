#pragma once

#include <map>
#include <string>
#include "Player.h"

class Room;

class Game
{
public:
    Game();
    void run();
    void stop();
    void player_joins_game(Player& player);
private:
    void init();
    bool running_ = false;
    std::map<std::string, Room*> rooms_;
};