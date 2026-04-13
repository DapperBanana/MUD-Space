#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <map>

class Room {
public:
    std::string name;
    std::string description;
    std::map<std::string, Room*> exits; // Direction -> Room*
    std::vector<std::string> objects;

    Room(const std::string& name, const std::string& description);
};

#endif
