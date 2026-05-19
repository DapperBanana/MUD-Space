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
            return "You are floating in an empty void.\r\n";
        }
    };
    handlers_["north"] = [](Session& session, const ParsedCommand& /*cmd*/) -> std::string {
        return session.handle_move("north");
    };
    handlers_["south"] = [](Session& session, const ParsedCommand& /*cmd*/) -> std::string {
        return session.handle_move("south");
    };
    handlers_["east"] = [](Session& session, const ParsedCommand& /*cmd*/) -> std::string {
        return session.handle_move("east");
    };
    handlers_["west"] = [](Session& session, const ParsedCommand& /*cmd*/) -> std::string {
        return session.handle_move("west");
    };
    handlers_["get"] = [](Session& session, const ParsedCommand& cmd) -> std::string {
        return session.handle_get(cmd);
    };

}

CommandHandler CommandDispatcher::get_handler(const std::string& verb) {
    auto it = handlers_.find(verb);
    if (it != handlers_.end()) {
        return it->second;
    } else {
        return default_handler_;
    }
}

std::string CommandDispatcher::default_handler_(Session& /*session*/, const ParsedCommand& /*cmd*/) {
    return "Invalid command.\r\n";
}
