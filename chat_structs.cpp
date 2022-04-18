#include "./json.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;

std::string json2string(json j) {
    std::string s = j.dump();
    return s;
}

json string2json(std::string s) {
    json j = json::parse(s);
    return j;
}


