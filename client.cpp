#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include "./client_responses.cpp"
#include "./async-sockets/tcpsocket.hpp"

int menuOptions()
{
    printf("1. Chatear con todos los usuarios (broadcasting).\n");
    printf("2. Enviar y recibir mensajes directos, privados, aparte del chat general.\n");
    printf("3. Cambiar de status.\n");
    printf("4. Listar los usuarios conectados al sistema de chat.\n");
    printf("5. Desplegar información de un usuario en particular.\n");
    printf("6. Ayuda.\n");
    printf("7. Salir.\n");
    printf("\n");
    printf("Ingrese una opción: ");
    int option;
    scanf("%d", &option);
    return option;
}

void onClientMessageReceived(std::string message, TCPSocket socket)
{
    try
    {
        std::list<std::string> jsonList = splitjsons(message);

        for (std::list<std::string>::iterator it = jsonList.begin(); it != jsonList.end(); ++it)
        {

            std::string jsonString = *it;

            json data = string2json(jsonString);

            std::string type = data["response"];
            json code = data["code"];

            if (type == "INIT_CONEX")
            {

                if (code == 200)
                {

                    json request_chats;
                    request_chats["request"] = "GET_CHAT";
                    request_chats["body"] = "all";
                    socket.Send(json2string(request_chats));

                }
                else if (code == 101)
                {
                    socket.Close();
                    printf("Conexion al chat rechazada...\n");
                    exit(0);
                }
            }
            else if (type == "END_CONEX")
            {
                printf("Conexion al chat terminada...\n");
                socket.Close();
                exit(0);
            }
            else if (type == "GET_CHAT")
            {
                printf(message.c_str());
            }
            else if (type == "POST_CHAT")
            {
            }
            else if (type == "GET_USER")
            {
                printf(message.c_str());
            }
            else if (type == "PUT_STATUS")
            {
            }
            else if (type == "NEW_MESSAGE")
            {
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }
}

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        printf("Error: Cantidad de argumentos incorrecta.\n");
        return -1;
    }

    // nombre del cliente
    char *clientName = argv[0];

    // nombre de usuario
    char *userName = argv[1];

    // ip del servidor
    char *serverIP = argv[2];

    // puerto del servidor
    int serverPort = atoi(argv[3]);

    TCPSocket tcpSocket([](int errorCode, std::string errorMessage)
                        { std::cout << "Socket creation error:" << errorCode << " : " << errorMessage << std::endl; });

    tcpSocket.onMessageReceived = [&](std::string message)
    {
        onClientMessageReceived(message, tcpSocket);
    };

    tcpSocket.onSocketClosed = [](int errorCode)
    {
        std::cout << "\n\nConnection closed: " << errorCode << std::endl;
        exit(0);
    };

    tcpSocket.Connect(
        serverIP, serverPort, [&]
        {
        json body;
        body["user_id"] = std::string(userName);
        body["connect_time"] = std::to_string(time(NULL));

        json connection;
        connection["request"] = "INIT_CONEX";
        connection["body"] = body;

        // Send String:
        tcpSocket.Send(json2string(connection)); },
        [](int errorCode, std::string errorMessage)
        {
            printf("Error: %s\n", errorMessage.c_str());
        });

    bool running = true;

    while (running)
    {

        int option = menuOptions();

        if (option == 2)
        {

            // message with userName
            json request_chats;
            request_chats["request"] = "GET_CHAT";
            request_chats["body"] = "all";
            tcpSocket.Send(json2string(request_chats));
        }
        else if (option == 7)
        {
            json request;
            request["request"] = "END_CONEX";
            tcpSocket.Send(json2string(request));
        }
    }

    tcpSocket.Close();

    return 0;
}
