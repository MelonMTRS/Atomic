#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "./Parser.h"
#include "../Exceptions.h"
#include "../Functions.h"

/*
    just a note here:
    This is not a complete parser for cfg files
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

config::Config::Config(const std::string& filename)
    : m_filename{filename}
{
    std::map<std::string, std::string> configData = {};
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
            configData[strip(s[0])] = strip(s[1]);
    }
    this->m_data = configData;
}

int const config::Config::getInt(const std::string& key) {
    return std::stoi(this->m_data[key]);
}

int64_t const config::Config::getInt64(const std::string& key) {
    return std::stoll(this->m_data[key]);
}

bool const config::Config::getBool(const std::string& key) {
    std::string val = atomic::lower(strip(this->m_data[key]));
    if (val == "true")
        return true;
    else if (val == "false")
        return false;
    throw atomic::UnknownValue{ "Unknown value" };
}

std::string const config::Config::getString(const std::string& key) {
    return this->m_data[key];
}