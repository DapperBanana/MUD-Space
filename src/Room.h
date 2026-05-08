#pragma once

#include <string>
#include <map>

class Room {
public:
    std::string name;
    std::string description;
    std::map<std::string, Room*> exits; // Direction -> Room*

    Room(const std::string& name, const std::string& description);
};
