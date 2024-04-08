//
// Created by Nic on 7/02/2024.
//

#include "util.h"

#include <algorithm>
#include <stdexcept>

void util::lower(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](const char c) { return std::tolower(c); });
}

int util::parsePositiveInt(const std::string &str)
{
    try {
        return std::stoi(str);
    } catch(std::invalid_argument const &ex) {
    } catch(std::out_of_range const &ex) {
    }

    return -1;
}

void util::splitArguments(std::string &line, std::vector<std::string> &args)
{
    const auto firstArg = line.find(' ');
    auto separator = firstArg;
    args.clear();

    while(separator != std::string::npos) {
        const auto nextSeparator = line.find(' ', separator + 1);

        if(nextSeparator == std::string::npos) {
            args.push_back(line.substr(separator + 1));
        } else {
            args.push_back(line.substr(separator + 1, nextSeparator - separator - 1));
        }

        separator = nextSeparator;
    }

    if(firstArg != std::string::npos) {
        line.erase(firstArg);
    }
}
