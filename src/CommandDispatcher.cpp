#include "CommandDispatcher.h"
#include "Session.h"
#include <sstream>

CommandDispatcher::CommandDispatcher()
{
    register_defaults();
}

void CommandDispatcher::register_defaults()
{
    handlers_["look"] = [](Session& /*session*/, const ParsedCommand& /*cmd*/) -> std::string {
        return "You are floating in an empty void. Stars glimmer faintly in every direction.\r\n";
    };

    handlers_["say"] = [](Session& /*session*/, const ParsedCommand& cmd) -> std::string {
        if (cmd.args.empty()) {
            return "Say what?\r\n";
        }
        std::ostringstream oss;
        oss << "You say: ";
        for (std::size_t i = 0; i < cmd.args.size(); ++i) {
            if (i > 0) oss << " ";
            oss << cmd.args[i];
        }
        oss << "\r\n";
        return oss.str();
    };

    handlers_["help"] = [](Session& /*session*/, const ParsedCommand& /*cmd*/) -> std::string {
        return "Available commands:\r\n"
               "  look  - Observe your surroundings\r\n"
               "  say   - Say something\r\n"
               "  help  - Show this help\r\n"
               "  quit  - Disconnect\r\n";
    };

    handlers_["quit"] = [](Session& session, const ParsedCommand& /*cmd*/) -> std::string {
        session.disconnect();
        return "Goodbye, spacefarer.\r\n";
    };
}

std::string CommandDispatcher::dispatch(Session& session, const ParsedCommand& cmd)
{
    if (cmd.verb.empty()) {
        return "";
    }

    auto it = handlers_.find(cmd.verb);
    if (it != handlers_.end()) {
        return it->second(session, cmd);
    }

    return "Unknown command: " + cmd.verb + ". Type 'help' for a list of commands.\r\n";
}
