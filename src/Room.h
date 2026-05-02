#pragma once

#include <string>
#include <vector>
#include <memory>

class Session;

class Room {
public:
    std::string name;
    std::string description;
    std::vector<std::weak_ptr<Session>> sessions; // Store weak pointers to avoid ownership issues

    Room(const std::string& name, const std::string& description);
};
