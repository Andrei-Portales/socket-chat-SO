#include <cstdlib>
#include <cstdio>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <pthread.h>

#include "./async-sockets/tcpserver.hpp"
#include "./server_responses.cpp"

connection_info conections[MAX_CONNECTIONS];

// chat_message *messages = new chat_message[0];
std::list<chat_message> messages;

int addConnection(std::string userName, TCPSocket *socket)
{
    bool userNameExists = false;
    bool availableConnection = false;
    int connectionIndex = -1;

    for (int i = 0; i < MAX_CONNECTIONS; i++)
    {
        if (conections[i].userName == userName)
        {
            userNameExists = true;
        }
    }

    for (int i = 0; i < MAX_CONNECTIONS; i++)
    {
        if (conections[i].userName == "" && conections[i].socket == NULL)
        {
            availableConnection = true;
            connectionIndex = i;
        }
    }

    if (!userNameExists && availableConnection)
    {
        conections[connectionIndex].userName = userName;
        conections[connectionIndex].status = 0;
        conections[connectionIndex].socket = socket;

        return 0;
    }

    return -1;
}

int removeConnection(std::string remoteAddres, int remotePort)
{
    for (int i = 0; i < MAX_CONNECTIONS; i++)
    {

        TCPSocket *socket = conections[i].socket;

        if (socket != NULL)
        {
            std::string remoteAddresSocket = socket->remoteAddress();
            int remotePortSocket = socket->remotePort();

            if (remoteAddres == remoteAddresSocket && remotePort == remotePortSocket)
            {
                conections[i].userName = "";
                conections[i].status = -1;
                conections[i].socket = NULL;
                return 0;
            }
        }
    }
    return -1;
}

void addMessageGlobal(json data)
{
    std::string message = data["message"];
    std::string from = data["from"];
    std::string delivered_at = getTimeString();
    std::string to = data["to"];

    chat_message message_var;
    message_var.message = message;
    message_var.from = from;
    message_var.delivered_at = delivered_at;
    message_var.to = to;

    messages.push_back(message_var);
}

void emitBroadcast(json data)
{
    for (int i = 0; i < MAX_CONNECTIONS; i++)
    {
        TCPSocket *socket = conections[i].socket;

        if (socket != NULL)
        {
            socket->Send(json2string(data));
        }
    }
}

void onClientMessageReceived(std::string message, TCPSocket *newClient)
{
    try
    {

        std::list<std::string> jsonList = splitjsons(message);

        for (std::list<std::string>::iterator it = jsonList.begin(); it != jsonList.end(); ++it)
        {
            std::string jsonString = *it;
            printf("%s:%d -> %s\n", newClient->remoteAddress().c_str(), newClient->remotePort(), jsonString.c_str());

            json data = string2json(jsonString);

            std::string type = data["request"];
            json body = data["body"];

            if (type == "INIT_CONEX")
            {
                std::string userName = body["user_id"];
                int rP = newClient->remotePort();
                std::string remotePort = std::to_string(rP);

                int addConnectionResult = addConnection(userName, newClient);

                json response;
                response["response"] = "INIT_CONEX";

                if (addConnectionResult != 0)
                {
                    response["code"] = 101;
                }
                else
                {
                    response["code"] = 200;
                }
                newClient->Send(json2string(response));

                json users_string = get_users_connected(conections);
                emitBroadcast(users_string);
            }
            else if (type == "END_CONEX")
            {
                int r = removeConnection(newClient->remoteAddress(), newClient->remotePort());

                json response;
                response["response"] = "END_CONEX";

                if (r == 0)
                {
                    response["code"] = 200;
                }
                else
                {
                    response["code"] = 105;
                }
                newClient->Send(json2string(response));

                json users_string = get_users_connected(conections);
                emitBroadcast(users_string);
            }
            else if (type == "GET_CHAT")
            {
                if (body == "all")
                {
                    json response = get_chats_all(messages);
                    newClient->Send(json2string(response));
                }
                else
                {
                    std::string userName = body;
                    json response = get_chats_user(messages, userName);
                    newClient->Send(json2string(response));
                }
            }
            else if (type == "POST_CHAT")
            {
                addMessageGlobal(body);

                json response;
                response["response"] = "POST_CHAT";
                response["code"] = 200;

                newClient->Send(json2string(response));

                json response_to_all;
                response_to_all["response"] = "NEW_MESSAGE";
                response_to_all["body"] = body;

                emitBroadcast(response_to_all);
            }
            else if (type == "GET_USER")
            {
                if (body == "all")
                {
                    json users_string = get_users_connected(conections);
                    newClient->Send(json2string(users_string));
                }
                else
                {
                    std::string userName = body;

                    std::string ip = "";
                    int status = -1;

                    for (int i = 0; i < MAX_CONNECTIONS; i++)
                    {
                        if (conections[i].socket != NULL && conections[i].userName == userName)
                        {
                            ip = conections[i].socket->remoteAddress();
                            status = conections[i].status;
                        }
                    }

                    json response;
                    response["response"] = "GET_USER";

                    if (ip == "" && status == -1)
                    {
                        response["code"] = 102;
                    }
                    else
                    {
                        response["code"] = 200;
                        json r = json::array();
                        r.push_back(ip);
                        std::string statusString = std::to_string(status);
                        r.push_back(statusString);
                        response["body"] = r;
                    }
                    newClient->Send(json2string(response));
                }
            }
            else if (type == "PUT_STATUS")
            {
                int status = body;

                bool find = false;

                for (int i = 0; i < MAX_CONNECTIONS; i++)
                {

                    if (conections[i].socket != NULL)
                    {
                        if (conections[i].socket->remoteAddress() == newClient->remoteAddress() && conections[i].socket->remotePort() == newClient->remotePort())
                        {
                            conections[i].status = status;

                            json response;
                            response["response"] = "PUT_STATUS";
                            response["code"] = 200;

                            newClient->Send(json2string(response));
                            find = true;

                            std::cout << "PUT_STATUS: " << conections[i].socket->remoteAddress() << ":" << conections[i].socket->remotePort() << " -> " << conections[i].status << std::endl;
                        }
                    }
                }

                if (!find)
                {
                    json response;
                    response["response"] = "PUT_STATUS";
                    response["code"] = 104;

                    newClient->Send(json2string(response));
                }


                json users_string = get_users_connected(conections);
                emitBroadcast(users_string);
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Error: Cantidad de argumentos incorrecta.\n");
        return -1;
    }

    // nombre del cliente
    char *serverName = argv[0];

    // puerto del servidor
    int serverPort = atoi(argv[1]);

    TCPServer tcpServer;

    tcpServer.onNewConnection = [&](TCPSocket *newClient)
    {
        printf("Nueva conexión  %s:%d \n", newClient->remoteAddress().c_str(), newClient->remotePort());

        newClient->onMessageReceived = [newClient](std::string message)
        {
            onClientMessageReceived(message, newClient);
        };

        newClient->onSocketClosed = [newClient](int errorCode)
        {
            removeConnection(newClient->remoteAddress(), newClient->remotePort());
            json users_string = get_users_connected(conections);
            emitBroadcast(users_string);
            printf("Client %s:%d disconnected.\n", newClient->remoteAddress().c_str(), newClient->remotePort());
        };
    };

    // Bind the server to a port.
    tcpServer.Bind(serverPort, [](int errorCode, std::string errorMessage)
                   {
        if (errorCode != 0)
        {
            printf("Error: %s\n", errorMessage.c_str());
            exit(1);
        }
        else
        {
            printf("Server started.\n");
        } });

    // Start Listening the server.
    tcpServer.Listen([](int errorCode, std::string errorMessage)
    {
        if (errorCode != 0)
        {
            printf("Error: %s\n", errorMessage.c_str());
            exit(1);
        }
        else
        {
            printf("Server listening.\n");
        } });

    std::string input;
    getline(std::cin, input);
    while (input != "exit")
    {
        getline(std::cin, input);
    }

    tcpServer.Close();

    return 0;
}