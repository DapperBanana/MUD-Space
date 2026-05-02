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
    handlers_["say"] = [](Session& session, const ParsedCommand& cmd) -> std::string {
        if (cmd.args.empty()) {
            return "Say what?\r\n";
        }
        std::stringstream ss;
        for (const auto& arg : cmd.args) {
            ss << arg << " ";
        }
        std::string message = ss.str();
        // Remove trailing space
        if (!message.empty()) {
            message.pop_back();
        }

        // Construct the full message with the player's name
        std::stringstream full_message;
        full_message << session.player_.name << " says: " << message << "\r\n";
        std::string full_message_str = full_message.str();

        // Broadcast the message to all sessions in the same room
        if (session.player_.currentRoom != nullptr) {
            for (auto& other_session : session.player_.currentRoom->sessions) {
                if (other_session.get() != &session) { // Don't send the message back to the sender
                    other_session->send(full_message_str);
                }
            }
            return "You say: " + message + "\r\n";
        } else {
            return "You are floating in an empty void. No one can hear you.\r\n";
        }
    };
}
