#include "../Exceptions.h"
#include "./Parser.h"
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

std::vector<std::string> split(std::string str, char separator) {
    std::vector<std::string> sp = {};
    std::string buffer = "";
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == separator) {
            sp.push_back(buffer);
            buffer = "";
            continue;
        }
        buffer += str[i];
    }
    if (buffer != "")
        sp.push_back(buffer);
    return sp;
}

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
        std::vector<std::string> s = split(line, '=');
        if (s.size() == 2)
            f[strip(s[0])] = strip(s[1]);
        else
            continue;
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