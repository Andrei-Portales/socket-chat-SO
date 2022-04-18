#include <cstdlib>
#include <cstdio>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include "./chat_structs.cpp"
#include "./async-sockets/tcpserver.hpp"
#include <pthread.h>

#define MAX_CONNECTIONS 10

connection_info conections[MAX_CONNECTIONS];

int addConnection(std::string remotePort, std::string userName, TCPSocket *socket)
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
        if (conections[i].remotePort == "" && conections->userName == "")
        {
            availableConnection = true;
            connectionIndex = i;
        }
    }

    if (!userNameExists && availableConnection)
    {
        conections[connectionIndex].userName = userName;
        conections[connectionIndex].remotePort = remotePort;
        conections[connectionIndex].socket = socket;

        return 0;
    }

    return -1;
}

int removeConnection(std::string userName)
{
    for (int i = 0; i < MAX_CONNECTIONS; i++)
    {
        if (conections[i].userName == userName)
        {
            conections[i].userName = "";
            conections[i].remotePort = "";
            conections[i].socket = NULL;
            return 0;
        }
    }
    return -1;
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

        
            int addConnectionResult = addConnection(remotePort, userName, newClient);

            if (addConnectionResult != 0)
            {

                // TODO: Send result to client
            }else {
                printf("Conexion aceptada de: %s %s:%s\n", userName.c_str(), newClient->remoteAddress().c_str(), remotePort.c_str());
                // TODO: Send result to client
            }
        }
        else if (type == "END_CONEX")
        {
        }
        else if (type == "GET_CHAT")
        {
        }
        else if (type == "GET_CHAT")
        {
        }
        else if (type == "POST_CHAT")
        {
        }
        else if (type == "GET_USER")
        {
        }
        else if (type == "PUT_STATUS")
        {
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