#include "CommandParser.h"
#include <sstream>
#include <algorithm>

ParsedCommand CommandParser::parse(const std::string& raw_input)
{
    ParsedCommand cmd;
    std::string input = strip(raw_input);

    if (input.empty()) {
        return cmd;
    }

    std::istringstream stream(input);
    std::string token;

    if (stream >> token) {
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        cmd.verb = token;
    }

    while (stream >> token) {
        cmd.args.push_back(token);
    }

    // Add support for direction commands
    if (cmd.verb == "n" || cmd.verb == "north") {
        cmd.verb = "north";
    } else if (cmd.verb == "s" || cmd.verb == "south") {
        cmd.verb = "south";
    } else if (cmd.verb == "e" || cmd.verb == "east") {
        cmd.verb = "east";
    } else if (cmd.verb == "w" || cmd.verb == "west") {
        cmd.verb = "west";
    }

    return cmd;
}

std::string CommandParser::strip(const std::string& input)
{
    std::string result = input;
    size_t start = result.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    result = result.substr(start);
    size_t end = result.find_last_not_of(" \t\r\n");
    if (end == std::string::npos) {
        return "";
    }
    result = result.substr(0, end + 1);
    return result;
}
