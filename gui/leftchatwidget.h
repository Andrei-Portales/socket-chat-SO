/********************************************************************************
** Form generated from reading UI file 'leftchatwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LEFTCHATWIDGET_H
#define LEFTCHATWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatItem
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *txtUsername;
    QSpacerItem *horizontalSpacer;
    QLabel *txtMessage;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *txtTime;

    void setupUi(QWidget *ChatItem)
    {
        if (ChatItem->objectName().isEmpty())
            ChatItem->setObjectName(QString::fromUtf8("ChatItem"));
        ChatItem->resize(416, 188);
        gridLayout_2 = new QGridLayout(ChatItem);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget = new QWidget(ChatItem);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        txtUsername = new QLabel(widget);
        txtUsername->setObjectName(QString::fromUtf8("txtUsername"));

        horizontalLayout->addWidget(txtUsername);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        txtMessage = new QLabel(widget);
        txtMessage->setObjectName(QString::fromUtf8("txtMessage"));
        txtMessage->setStyleSheet(QString::fromUtf8("#txtMessage {\n"
"	border-top: 1px solid black;\n"
"	border-bottom: 1px solid black;\n"
"}"));

        verticalLayout->addWidget(txtMessage);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        txtTime = new QLabel(widget);
        txtTime->setObjectName(QString::fromUtf8("txtTime"));

        horizontalLayout_2->addWidget(txtTime);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_2->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(ChatItem);

        QMetaObject::connectSlotsByName(ChatItem);
    } // setupUi

    void retranslateUi(QWidget *ChatItem)
    {
        ChatItem->setWindowTitle(QApplication::translate("ChatItem", "Form", nullptr));
        txtUsername->setText(QApplication::translate("ChatItem", "Andrei", nullptr));
        txtMessage->setText(QApplication::translate("ChatItem", "Hola mundo", nullptr));
        txtTime->setText(QApplication::translate("ChatItem", "10:24 pm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatItem: public Ui_ChatItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LEFTCHATWIDGET_H
