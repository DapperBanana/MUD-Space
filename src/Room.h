#pragma once

#include <string>
#include <vector>

class Item {
public:
    std::string name;
    std::string description;

    Item(const std::string& name, const std::string& description) : name(name), description(description) {}
};

class Room {
public:
    std::string name;
    std::string description;
    std::vector<Item> items;

    Room(const std::string& name, const std::string& description);
    std::string describe_items() const;
};
