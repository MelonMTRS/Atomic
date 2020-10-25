#include "../Exceptions.h"
#include "../Functions.h"
#include "./Parser.h"
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

/*
    just a note here:
    this entire code was made a while ago and hasn't been updated much since
    i'm planning to revamp when I finish most of the important stuff in atomic
    but for now, it does the job
*/

std::string strip(std::string s) {
    while (s.front() == ' ' || s.back() == ' ') {
        if (s.front() == ' ')
            s.erase(0, 1);
        if (s.back() == ' ')
            s.pop_back();
    }
    return s;
}

bool isdigit(std::string s) {
    for (char c : s) {
        if (std::isdigit(c) == 0)
            return false;
    }
    return true;
}


config::Parser config::parse(std::string filename) {
    config::Parser f = {};
    std::ifstream config{ filename };
    if (!config)
        throw atomic::ConfigLoadFailure{};
    while (config) {
        std::string line;
        std::getline(config, line);
        if (line[0] == '#' || line[0] == '[')
            continue;
        std::vector<std::string> s = atomic::split(line, '=');
        if (s.size() == 2)
            f[strip(s[0])] = strip(s[1]);
    }
    return f;
}

config::ParseValue config::get(config::Parser ParseObject, std::string key) {
    try {
        ParseObject.at(key);
    }
    catch (std::out_of_range) {
        throw atomic::ItemFetchFailure{};
    }
    std::string value = ParseObject[key];
    if (value == "true")
        return true;
    else if (value == "false")
        return false;
    else if (isdigit(value))
        return std::stoi(value);
    return value;
}