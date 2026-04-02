#pragma once

#include <string>
#include <vector>

struct ParsedCommand {
    std::string verb;
    std::vector<std::string> args;

    bool empty() const { return verb.empty(); }
};

class CommandParser {
public:
    static ParsedCommand parse(const std::string& raw_input);

private:
    static std::string strip(const std::string& input);
};
