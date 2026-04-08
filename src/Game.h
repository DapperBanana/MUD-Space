#pragma once

#include <string>
#include <unordered_map>

class Game
{
public:
    Game();
    void run();

private:
    bool running_ = false;

    struct Player
    {
        std::string name;
    };

    std::unordered_map<size_t, Player> players_;
};
