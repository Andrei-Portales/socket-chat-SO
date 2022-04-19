#include <cstdlib>
#include <cstdio>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <pthread.h>

#include "./chat_structs.cpp"
#include "./async-sockets/tcpserver.hpp"

#define MAX_CONNECTIONS 10

connection_info conections[MAX_CONNECTIONS];

chat_message *messages = new chat_message[0];

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
        if (conections[i].socket->remoteAddress() == remoteAddres && conections[i].socket->remotePort() == remotePort)
        {
            conections[i].userName = "";
            conections[i].status = -1;
            conections[i].socket = NULL;
            return 0;
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

    chat_message temp[sizeof(messages) + 1];

    for (int i = 0; i < sizeof(messages); i++)
    {
        temp[i] = messages[i];
    }
    temp[sizeof(messages)] = message_var;
    messages = temp;
}

void onClientMessageReceived(std::string message, TCPSocket *newClient)
{
    try
    {
        printf("Mensaje recibido: %s\n", message.c_str());
        json data = string2json(message);

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
                printf("Conexion aceptada de: %s %s:%s\n", userName.c_str(), newClient->remoteAddress().c_str(), remotePort.c_str());
                response["code"] = 200;
            }
            newClient->Send(json2string(response));
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
        }
        else if (type == "GET_CHAT")
        {
            if (body == "all")
            {
                json body[sizeof(messages)];

                for (int i = 0; i < sizeof(messages); i++)
                {
                    body[i]["message"] = messages[i].message;
                    body[i]["from"] = messages[i].from;
                    body[i]["delivered_at"] = messages[i].delivered_at;
                    body[i]["to"] = messages[i].to;
                }

                json response;
                response["response"] = "GET_CHAT";
                response["code"] = 200;
                response["body"] = body;

                newClient->Send(json2string(response));
            }
            else
            {
                std::string userName = body;

                json *body = new json[0];

                for (int i = 0; i < sizeof(messages); i++)
                {
                    if (messages[i].to == userName)
                    {
                        json message;
                        message["message"] = messages[i].message;
                        message["from"] = messages[i].from;
                        message["delivered_at"] = messages[i].delivered_at;
                        message["to"] = messages[i].to;

                        json temp[sizeof(body) + 1];
                        for (int j = 0; j < sizeof(body); j++)
                        {
                            temp[j] = body[j];
                        }
                        temp[sizeof(body)] = message;
                        body = temp;
                    }
                }

                json response;
                response["response"] = "GET_CHAT";
                response["code"] = 200;

                json bodyjson[sizeof(body)];

                for (int i = 0; i < sizeof(body); i++)
                {
                    bodyjson[i]["message"] = body[i]["message"];
                    bodyjson[i]["from"] = body[i]["from"];
                    bodyjson[i]["delivered_at"] = body[i]["delivered_at"];
                    bodyjson[i]["to"] = body[i]["to"];
                }

                response["body"] = bodyjson;

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

            for (int i = 0; i < MAX_CONNECTIONS; i++)
            {
                if (conections[i].socket != NULL && conections[i].status > 0)
                {
                    conections[i].socket->Send(json2string(response_to_all));
                }
            }
        }
        else if (type == "GET_USER")
        {
            if (body == "all")
            {
                json *body = new json[0];

                for (int i = 0; i < MAX_CONNECTIONS; i++)
                {
                    if (conections[i].status == 0)
                    {
                        json temp[sizeof(body) + 1];

                        for (int j = 0; j < sizeof(body); j++)
                        {
                            temp[j] = body[j];
                        }
                        temp[sizeof(body)] = conections[i].userName;
                        body = temp;
                    }
                }

                json response;
                response["response"] = "GET_USER";
                response["code"] = 200;

                json bodyjson[sizeof(body)];

                for (int i = 0; i < sizeof(body); i++)
                {
                    bodyjson[i]["message"] = body[i]["message"];
                    bodyjson[i]["from"] = body[i]["from"];
                    bodyjson[i]["delivered_at"] = body[i]["delivered_at"];
                    bodyjson[i]["to"] = body[i]["to"];
                }

                response["body"] = bodyjson;

                newClient->Send(json2string(response));
            }
            else
            {
                std::string userName = body;

                std::string ip = "";

                for (int i = 0; i < MAX_CONNECTIONS; i++)
                {
                    if (conections[i].userName == userName)
                    {
                        ip = conections[i].socket->remoteAddress();
                    }
                }

                json response;
                response["response"] = "GET_USER";

                if (ip == "")
                {
                    response["code"] = 102;
                }
                else
                {
                    response["code"] = 200;
                    response["body"] = ip;
                }
            }
        }
        else if (type == "PUT_STATUS")
        {
            int status = body;

            for (int i = 0; i < MAX_CONNECTIONS; i++)
            {
                if (conections[i].socket->remoteAddress() == newClient->remoteAddress() && conections[i].socket->remotePort() == newClient->remotePort())
                {
                    conections[i].status = status;

                    json response;
                    response["response"] = "PUT_STATUS";
                    response["code"] = 200;

                    newClient->Send(json2string(response));
                    break;
                }
            }

            json response;
            response["response"] = "PUT_STATUS";
            response["code"] = 104;

            newClient->Send(json2string(response));
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