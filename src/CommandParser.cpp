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

    return cmd;
}

std::string CommandParser::strip(const std::string& input)
{
    std::string result = input;
    result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());

    size_t start = result.find_first_not_of(' ');
    if (start == std::string::npos) return "";
    size_t end = result.find_last_not_of(' ');
    return result.substr(start, end - start + 1);
}
