#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include "./client_responses.cpp"
#include "./async-sockets/tcpsocket.hpp"

// qt interface
#include <QApplication>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
#include <QMenu>
#include "./gui/mainwindow.h"

std::list<chat_message> messages;
std::list<user> users;
std::string currentChat = "all";
int status = 0;
int newStatus = 0;

void insertChatsToGui(std::list<chat_message> messages, Ui::ChatWindow ui)
{

    std::string userName = ui.txtUserChat->text().toStdString();

    ui.messagesListWidget->clear();

    for (auto it = messages.begin(); it != messages.end(); it++)
    {
        if ((it->to == currentChat && it->from == userName) || (it->to == userName && it->from == currentChat))
        {
            std::string from = it->from;

            if (from == userName)
            {
                from = "You";
            }

            std::string messageString = from + " (" + it->delivered_at + "): " + it->message;
            ui.messagesListWidget->addItem(QString::fromStdString(messageString));
        }
        else if (it->to == "all" && currentChat == "all")
        {
            std::string from = it->from;

            if (from == userName)
            {
                from = "You";
            }

            std::string messageString = from + " (" + it->delivered_at + "): " + it->message;
            ui.messagesListWidget->addItem(QString::fromStdString(messageString));
        }
    }
}

void onClientMessageReceived(std::string message, TCPSocket socket, Ui::ChatWindow ui)
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
                    ui.label_username->setText(QString::fromStdString("Usuario: " + ui.txtUserChat->text().toStdString()));
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

                insertChatsToGui(messages, ui);
            }
            else if (type == "POST_CHAT")
            {
                if (code == 200)
                {
                }
            }
            else if (type == "GET_USER")
            {
                int code = data["code"];

                if (code == 200)
                {
                    json body = data["body"];

                    if (body.is_array())
                    {

                        int size = body.size();

                        if (size > 0 && body[0].is_array())
                        {
                            users.clear();

                            user all;
                            all.userName = "Todos los usuarios";
                            all.status = 0;

                            users.push_back(all);

                            for (int i = 0; i < body.size(); i++)
                            {
                                json user_json = body[i];

                                user user_data;
                                user_data.userName = user_json[0];
                                user_data.status = atoi(user_json[1]);
                                users.push_back(user_data);
                            }

                            ui.usersListWidget->clear();
                            int index = 0;

                            for (auto it = users.begin(); it != users.end(); it++)
                            {
                                std::string currentUser = ui.txtUserChat->text().toStdString();

                                user user_item = *it;
                                if (currentUser != user_item.userName)
                                {
                                    ui.usersListWidget->addItem(QString::fromStdString(user_item.userName));

                                    QBrush brush;

                                    if (user_item.status == 0)
                                    {
                                        brush.setColor(QColor(0, 255, 0));
                                    }
                                    else if (user_item.status == 1)
                                    {
                                        brush.setColor(QColor(168, 168, 168));
                                    }
                                    else if (user_item.status == 2)
                                    {
                                        brush.setColor(QColor(255, 0, 0));
                                    }
                                    else
                                    {
                                        brush.setColor(QColor(0, 0, 0));
                                    }

                                    ui.usersListWidget->item(index)->setForeground(brush);
                                    index++;
                                }
                            }
                        }
                    }
                }
            }
            else if (type == "PUT_STATUS")
            {

                if (code == 200)
                {
                    status = newStatus;

                    std::string estados[3] = {"Activo", "Inactivo", "Ocupado"};
                    ui.btnEstado->setText(QString::fromStdString(estados[status]));
                }
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

                insertChatsToGui(messages, ui);
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

    QObject::connect(ui.btnEntrar, &QPushButton::clicked, &w, [&]()
                     {
                         std::string userName = ui.txtUserChat->text().toStdString();
                         std::string serverIP = ui.txtIpChat->text().toStdString();
                         std::string serverPortString = ui.txtPortChat->text().toStdString();

                         if (userName.empty() || serverIP.empty() || serverPortString.empty())
                         {
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
                             }); });

    QObject::connect(ui.btnCerrarSesion, &QPushButton::clicked, &w, [&]()
                     {
        json connection;
        connection["request"] = "END_CONEX";
        tcpSocket.Send(json2string(connection)); });

    QObject::connect(ui.btnSendMessage, &QPushButton::clicked, &w, [&]()
                     {
        std::string message =  ui.txtMessage->text().toStdString();

        if (message.empty()){
            return;
        }

        json body;
        body["message"] = message;
        body["from"] = std::string(ui.txtUserChat->text().toStdString());
        body["to"] = currentChat;
        body["delivered_at"] = getTimeString();

        json connection;
        connection["request"] = "POST_CHAT";
        connection["body"] = body;

        tcpSocket.Send(json2string(connection));
        ui.txtMessage->clear(); });

    QObject::connect(ui.usersListWidget, &QListWidget::itemClicked, &w, [&](QListWidgetItem *item)
                     {
            // get index
            int index = ui.usersListWidget->row(item);

            if (index == 0)
            {
                currentChat = "all";
            }
            else
            {
                currentChat = item->text().toStdString();
            }

            insertChatsToGui(messages, ui); });

    QObject::connect(ui.btnRefrescar, &QPushButton::clicked, &w, [&]()
                     {
                         json request_chats;
                         request_chats["request"] = "GET_CHAT";
                         request_chats["body"] = "all";
                         tcpSocket.Send(json2string(request_chats));

                         json request_users;
                         request_users["request"] = "GET_USER";
                         request_users["body"] = "all";
                         tcpSocket.Send(json2string(request_users)); });

    QMenu *menu = new QMenu;
    menu->addAction(QString::fromStdString("Cambiar estado a activo"));
    menu->addAction(QString::fromStdString("Cambiar estado a inactivo"));
    menu->addAction(QString::fromStdString("Cambiar estado a ocupado"));

    QObject::connect(menu, &QMenu::triggered, &w, [&](QAction *action)
                     {

        int index = menu->actions().indexOf(action);

        json request;
        request["request"] = "PUT_STATUS";
        request["body"] = index;
        newStatus = index;
        tcpSocket.Send(json2string(request)); });

    ui.btnEstado->setMenu(menu);

    QObject::connect(ui.btnAyuda, &QPushButton::clicked, &w, [&]() {
        QMessageBox::information(nullptr, "Error", "No hay ayuda disponible");
    });

    w.show();

    // tcpSocket.Close();

    return a.exec();
}
