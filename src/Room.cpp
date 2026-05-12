#include "Room.h"
#include <sstream>

Room::Room(const std::string& name, const std::string& description)
    : name(name), description(description) {}

std::string Room::describe_items() const {
    if (items.empty()) {
        return "There are no items here.\r\n";
    }

    std::ostringstream oss;
    oss << "Items here:\r\n";
    for (const auto& item : items) {
        oss << "- " << item.name << ": " << item.description << "\r\n";
    }
    return oss.str();
}
