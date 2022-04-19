#include "./json.hpp"
#include <iostream>
#include <string>
#include "./async-sockets/tcpsocket.hpp"
#include <ctime>


using json = nlohmann::json;

struct connection_info {
    std::string userName = "";
    int status = -1;
    TCPSocket *socket = NULL;
};

struct chat_message {
    std::string message;
    std::string from;
    std::string delivered_at;
    std::string to;
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

std::string getTimeString(){
    time_t curr_time;
	tm * curr_tm;
	char date_string[100];
	char time_string[100];
	
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	
	strftime(date_string, 50, "%B %d, %Y", curr_tm);
	strftime(time_string, 50, "%T", curr_tm);
	
	return std::string(date_string) + " " + std::string(time_string);
}




