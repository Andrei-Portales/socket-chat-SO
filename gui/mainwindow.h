/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *pages;
    QWidget *login;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *txtUserChat;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *txtIpChat;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *txtPortChat;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btnEntrar;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QWidget *users;
    QWidget *chat;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btnCerrarSesion;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout_3;
    QListWidget *listWidget_2;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName(QString::fromUtf8("ChatWindow"));
        ChatWindow->resize(800, 600);
        centralwidget = new QWidget(ChatWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pages = new QStackedWidget(centralwidget);
        pages->setObjectName(QString::fromUtf8("pages"));
        login = new QWidget();
        login->setObjectName(QString::fromUtf8("login"));
        gridLayout_2 = new QGridLayout(login);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(login);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        txtUserChat = new QLineEdit(login);
        txtUserChat->setObjectName(QString::fromUtf8("txtUserChat"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txtUserChat->sizePolicy().hasHeightForWidth());
        txtUserChat->setSizePolicy(sizePolicy);
        txtUserChat->setMinimumSize(QSize(200, 0));
        txtUserChat->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(txtUserChat);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(login);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        txtIpChat = new QLineEdit(login);
        txtIpChat->setObjectName(QString::fromUtf8("txtIpChat"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(200);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txtIpChat->sizePolicy().hasHeightForWidth());
        txtIpChat->setSizePolicy(sizePolicy1);
        txtIpChat->setMinimumSize(QSize(200, 0));

        horizontalLayout_2->addWidget(txtIpChat);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(login);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        txtPortChat = new QLineEdit(login);
        txtPortChat->setObjectName(QString::fromUtf8("txtPortChat"));
        sizePolicy1.setHeightForWidth(txtPortChat->sizePolicy().hasHeightForWidth());
        txtPortChat->setSizePolicy(sizePolicy1);
        txtPortChat->setMinimumSize(QSize(200, 0));

        horizontalLayout_3->addWidget(txtPortChat);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        btnEntrar = new QPushButton(login);
        btnEntrar->setObjectName(QString::fromUtf8("btnEntrar"));
        btnEntrar->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btnEntrar);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        pages->addWidget(login);
        users = new QWidget();
        users->setObjectName(QString::fromUtf8("users"));
        pages->addWidget(users);
        chat = new QWidget();
        chat->setObjectName(QString::fromUtf8("chat"));
        gridLayout_3 = new QGridLayout(chat);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        btnCerrarSesion = new QPushButton(chat);
        btnCerrarSesion->setObjectName(QString::fromUtf8("btnCerrarSesion"));

        horizontalLayout_7->addWidget(btnCerrarSesion);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        listWidget = new QListWidget(chat);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy2);
        listWidget->setMinimumSize(QSize(225, 0));
        listWidget->setMaximumSize(QSize(225, 16777215));

        horizontalLayout_6->addWidget(listWidget);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        listWidget_2 = new QListWidget(chat);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));

        verticalLayout_3->addWidget(listWidget_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        lineEdit = new QLineEdit(chat);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_5->addWidget(lineEdit);

        pushButton = new QPushButton(chat);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_5->addWidget(pushButton);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_6);


        gridLayout_3->addLayout(verticalLayout_4, 0, 0, 1, 1);

        pages->addWidget(chat);

        gridLayout->addWidget(pages, 0, 0, 1, 1);

        ChatWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ChatWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ChatWindow->setStatusBar(statusbar);

        retranslateUi(ChatWindow);

        pages->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ChatWindow)
    {
        ChatWindow->setWindowTitle(QApplication::translate("ChatWindow", "Chat", nullptr));
        label->setText(QApplication::translate("ChatWindow", "Usuario", nullptr));
        label_2->setText(QApplication::translate("ChatWindow", "Ip del servidor", nullptr));
        label_3->setText(QApplication::translate("ChatWindow", "Puerto del servidor", nullptr));
        btnEntrar->setText(QApplication::translate("ChatWindow", "Entrar", nullptr));
        btnCerrarSesion->setText(QApplication::translate("ChatWindow", "Cerrar sesion", nullptr));
        pushButton->setText(QApplication::translate("ChatWindow", "Enviar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_H
