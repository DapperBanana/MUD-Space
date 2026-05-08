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
            return oss.str();
        } else {
            return "You are floating in an empty void. Stars glimmer faintly in every direction.\r\n";
        }
    };

    handlers_["north"] = [](Session& session, const ParsedCommand& /*cmd*/) -> std::string {
        if (session.player_.currentRoom != nullptr && session.player_.currentRoom->exits.count("north")) {
            session.player_.currentRoom = session.player_.currentRoom->exits["north"];
            std::ostringstream oss;
            oss << session.player_.currentRoom->description << "\r\n";
            return oss.str();
        } else {
            return "You cannot go that way.\r\n";
        }
    };

    handlers_["south"] = [](Session& session, const ParsedCommand& /*cmd*/) -> std::string {
        if (session.player_.currentRoom != nullptr && session.player_.currentRoom->exits.count("south")) {
            session.player_.currentRoom = session.player_.currentRoom->exits["south"];
            std::ostringstream oss;
            oss << session.player_.currentRoom->description << "\r\n";
            return oss.str();
        } else {
            return "You cannot go that way.\r\n";
        }
    };

    handlers_["east"] = [](Session& session, const ParsedCommand& /*cmd*/) -> std::string {
        if (session.player_.currentRoom != nullptr && session.player_.currentRoom->exits.count("east")) {
            session.player_.currentRoom = session.player_.currentRoom->exits["east"];
            std::ostringstream oss;
            oss << session.player_.currentRoom->description << "\r\n";
            return oss.str();
        } else {
            return "You cannot go that way.\r\n";
        }
    };

    handlers_["west"] = [](Session& session, const ParsedCommand& /*cmd*/) -> std::string {
        if (session.player_.currentRoom != nullptr && session.player_.currentRoom->exits.count("west")) {
            session.player_.currentRoom = session.player_.currentRoom->exits["west"];
            std::ostringstream oss;
            oss << session.player_.currentRoom->description << "\r\n";
            return oss.str();
        } else {
            return "You cannot go that way.\r\n";
        }
    };
}
