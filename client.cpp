#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include "./client_responses.cpp"
#include "./async-sockets/tcpsocket.hpp"

// qt interface
#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include "./gui/mainwindow.h"

std::list<chat_message> messages;

void onClientMessageReceived(std::string message, TCPSocket socket,  Ui::ChatWindow ui)
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

                    ui.pages->setCurrentIndex(2);
                }
                else if (code == 101)
                {
                    printf("Conexion al chat rechazada...\n");
                    QMessageBox::information(nullptr, "Error", "Debe llenar todos los campos");
                    socket.Close();
                }
            }
            else if (type == "END_CONEX")
            {
                printf("Conexion al chat terminada...\n");
                ui.pages->setCurrentIndex(0);
                printf("setcurrentindex: 0\n");

                socket.Close();
            }
            else if (type == "GET_CHAT")
            {

                json body = data["body"];

                messages.clear();

                for (int i = 0; i < body.size(); i++)
                {
                    json message = body[i];

                    std::string message_string = message["message"];
                    std::string from = message["from"];
                    std::string delivered_at = message["delivered_at"];
                    std::string to = message["to"];

                    chat_message chat_message;
                    chat_message.message = message_string;
                    chat_message.from = from;
                    chat_message.delivered_at = delivered_at;
                    chat_message.to = to;

                    messages.push_back(chat_message);
                }
            }
            else if (type == "POST_CHAT")
            {
                if (code == 200){
                  
                }
            }
            else if (type == "GET_USER")
            {
            }
            else if (type == "PUT_STATUS")
            {
            }
            else if (type == "NEW_MESSAGE")
            {
                json body = data["body"];

                chat_message message;
                message.message = body["message"];
                message.from = body["from"];
                message.delivered_at = body["delivered_at"];
                message.to = body["to"];

                messages.push_back(message);
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
    QApplication a(argc, argv);

    QMainWindow w;

    Ui::ChatWindow ui;

    ui.setupUi(&w);


    TCPSocket tcpSocket([](int errorCode, std::string errorMessage)
                        { std::cout << "Socket creation error:" << errorCode << " : " << errorMessage << std::endl; });

    tcpSocket.onMessageReceived = [&](std::string message)
    {
        onClientMessageReceived(message, tcpSocket, ui);
    };

    tcpSocket.onSocketClosed = [&](int errorCode)
    {
        std::cout << "\n\nConnection closed: " << errorCode << std::endl;
        ui.pages->setCurrentIndex(0);
    };

    QObject::connect(ui.btnEntrar, &QPushButton::clicked, &w, [&](){
        std::string userName =  ui.txtUserChat->text().toStdString();
        std::string serverIP =  ui.txtIpChat->text().toStdString();
        std::string serverPortString =  ui.txtPortChat->text().toStdString();
       

        if (userName.empty() || serverIP.empty() || serverPortString.empty()){
            QMessageBox::information(nullptr, "Error", "Debe llenar todos los campos");
            return;
        }

         int serverPort = std::stoi(serverPortString);

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

      
    });

    QObject::connect(ui.btnCerrarSesion, &QPushButton::clicked, &w, [&](){
        json connection;
        connection["request"] = "END_CONEX";
        tcpSocket.Send(json2string(connection));
    });


    w.show();

    // tcpSocket.Close();

    return a.exec();
}
