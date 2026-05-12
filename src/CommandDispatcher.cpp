#include "CommandDispatcher.h"
#include "Session.h"
#include <sstream>

CommandDispatcher::CommandDispatcher()
{
    register_defaults();
}

void CommandDispatcher::register_defaults()
{
    handlers_["look"] = [](Session& session, const ParsedCommand& /*cmd*/) -> std::string {
        if (session.player_.currentRoom != nullptr) {
            std::ostringstream oss;
            oss << session.player_.currentRoom->description << "\r\n";
            oss << session.player_.currentRoom->describe_items();
            return oss.str();
        } else {
            return "You are floating in an empty void. Stars glimmer faintly in every direction.\r\n";
        }
    };

    handlers_["get"] = [](Session& session, const ParsedCommand& cmd) -> std::string {
        if (cmd.args.empty()) {
            return "Get what?\r\n";
        }

        std::string itemName = cmd.args[0];
        Room* room = session.player_.currentRoom;
        if (room == nullptr) {
            return "You are floating in the void. There is nothing to get.\r\n";
        }

        for (size_t i = 0; i < room->items.size(); ++i) {
            if (room->items[i].name == itemName) {
                // Item found! Remove it from the room and add it to player inventory (not implemented yet)
                room->items.erase(room->items.begin() + i);
                return "You got the " + itemName + ".\r\n";
            }
        }

        return "There is no " + itemName + " here.\r\n";
    };
}
