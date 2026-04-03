#pragma once

#include "CommandParser.h"
#include <string>
#include <functional>
#include <unordered_map>

class Session;

class CommandDispatcher {
public:
    using Handler = std::function<std::string(Session&, const ParsedCommand&)>;

    CommandDispatcher();
    std::string dispatch(Session& session, const ParsedCommand& cmd);

private:
    void register_defaults();
    std::unordered_map<std::string, Handler> handlers_;
};
