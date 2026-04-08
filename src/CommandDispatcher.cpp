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
        for (const auto& arg : cmd.args) {
            oss << arg << " ";
        }
        oss << "\r\n";
        return oss.str();
    };

    handlers_["quit"] = [](Session& session, const ParsedCommand& /*cmd*/) -> std::string {
        session.close();
        return "Goodbye.\r\n";
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
    else {
        return "Huh?\r\n";
    }
}
