#include "./json.hpp"
#include <iostream>
#include <string>
#include "./async-sockets/tcpsocket.hpp"

using json = nlohmann::json;

struct connection_info {
    std::string remotePort;
    std::string userName;
    TCPSocket *socket;
};


std::string json2string(json j) {
    std::string s = j.dump();
    return s;
}

json string2json(std::string s) {
    json j = json::parse(s);
    return j;
}

json create_message(std::string message) {
    json j;
    j["message"] = message;
    return json2string(j);
}


