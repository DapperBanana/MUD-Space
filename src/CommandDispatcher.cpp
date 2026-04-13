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

    handlers_["say"] = [](Session& /*session*/, const ParsedCommand& cmd) -> std::string {
        if (cmd.args.empty()) {
            return "Say what?\r\n";
        }
        std::ostringstream oss;
        o