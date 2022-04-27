#include "./chat_structs.cpp"
#include <list>

#define MAX_CONNECTIONS 10

json get_chats_all(std::list<chat_message> messages)
{
    int messages_size = messages.size();
    json bodyResp = json::array();
    std::list<chat_message>::iterator it = messages.begin();

    for (int i = 0; i < messages_size; i++)
    {
        std::advance(it, i);
        chat_message cur_message = *it;

        std::cout << typeid(cur_message.message).name() << std::endl;

        json message;
        message["message"] = cur_message.message;
        message["from"] = cur_message.from;
        message["delivered_at"] = cur_message.delivered_at;
        message["to"] = cur_message.to;

        bodyResp.push_back(message);
    }

    json response;
    response["response"] = "GET_CHAT";
    response["code"] = 200;
    response["body"] = bodyResp;
   
    

    return response;
}

json get_chats_user(std::list<chat_message> messages, std::string userName)
{
    json body = json::array();

    std::list<chat_message>::iterator it = messages.begin();

    int messages_size = messages.size();

    for (int i = 0; i < messages_size; i++)
    {
        std::advance(it, i);
        chat_message cur_message = *it;

        if (cur_message.to == userName)
        {
            json message;

            message["message"] = cur_message.message;
            message["from"] = cur_message.from;
            message["delivered_at"] = cur_message.delivered_at;
            message["to"] = cur_message.to;

            body.push_back(message);
        }
    }

    json response;
    response["response"] = "GET_CHAT";
    response["code"] = 200;

    response["body"] = body;

    return response;
}

json get_users_connected(connection_info *conections)
{
    json body = json::array();

    for (int i = 0; i < MAX_CONNECTIONS; i++)
    {
        if (conections[i].status > -1 && conections[i].userName != "" && conections[i].socket != NULL)
        {
            json temp = json::array();
            temp.push_back(conections[i].userName);
            std::string statusString = std::to_string(conections[i].status);
            temp.push_back(statusString);

            body.push_back(temp);
        }
    }

    json response;
    response["response"] = "GET_USER";
    response["code"] = 200;
    response["body"] = body;

    std:: cout << response.dump() << std::endl;

    return response;
}

std::list<std::string> splitjsons(std::string jsonString)
{
    int left = 0;
    int right = 0;

    std::list<std::string> jsonList;

    std::string temp;


    for (int i = 0; i < jsonString.size(); i++)
    {
        if (jsonString[i] == '{')
        {
            left++;
        }

        if (jsonString[i] == '}')
        {
            right++;
        }

        temp += jsonString[i];

        if (left == right)
        {
            jsonList.push_back(temp);
            temp = "";
        }
    }

    return jsonList;
}