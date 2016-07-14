/********************************************************************************
** Form generated from reading UI file 'lobby.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOBBY_H
#define UI_LOBBY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lobby
{
public:
    QWidget *centralwidget;
    QLabel *background;
    QPushButton *refresh;
    QPushButton *addtofav;
    QPushButton *connect;
    QPushButton *publicservers;
    QPushButton *favorites;
    QListWidget *serverlist;

    void setupUi(QMainWindow *Lobby)
    {
        if (Lobby->objectName().isEmpty())
            Lobby->setObjectName(QStringLiteral("Lobby"));
        Lobby->resize(517, 666);
        Lobby->setMaximumSize(QSize(517, 666));
        QIcon icon;
        icon.addFile(QStringLiteral(":/resource/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        Lobby->setWindowIcon(icon);
        centralwidget = new QWidget(Lobby);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        background = new QLabel(centralwidget);
        background->setObjectName(QStringLiteral("background"));
        background->setGeometry(QRect(0, 0, 517, 666));
        background->setPixmap(QPixmap(QString::fromUtf8("../build-Attorney_Online_new-Desktop_Qt_5_7_0_GCC_64bit-Debug/base/themes/default/lobbybackground.png")));
        refresh = new QPushButton(centralwidget);
        refresh->setObjectName(QStringLiteral("refresh"));
        refresh->setGeometry(QRect(56, 381, 132, 28));
        refresh->setFlat(false);
        addtofav = new QPushButton(centralwidget);
        addtofav->setObjectName(QStringLiteral("addtofav"));
        addtofav->setGeometry(QRect(194, 381, 132, 28));
        addtofav->setFlat(false);
        connect = new QPushButton(centralwidget);
        connect->setObjectName(QStringLiteral("connect"));
        connect->setGeometry(QRect(332, 381, 132, 28));
        connect->setFlat(false);
        publicservers = new QPushButton(centralwidget);
        publicservers->setObjectName(QStringLiteral("publicservers"));
        publicservers->setGeometry(QRect(46, 88, 114, 30));
        publicservers->setFlat(false);
        favorites = new QPushButton(centralwidget);
        favorites->setObjectName(QStringLiteral("favorites"));
        favorites->setGeometry(QRect(164, 88, 114, 30));
        favorites->setFlat(false);
        serverlist = new QListWidget(centralwidget);
        serverlist->setObjectName(QStringLiteral("serverlist"));
        serverlist->setGeometry(QRect(20, 125, 286, 240));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 0));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(239, 235, 231, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        serverlist->setPalette(palette);
        QFont font;
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        serverlist->setFont(font);
        Lobby->setCentralWidget(centralwidget);

        retranslateUi(Lobby);

        QMetaObject::connectSlotsByName(Lobby);
    } // setupUi

    void retranslateUi(QMainWindow *Lobby)
    {
        Lobby->setWindowTitle(QApplication::translate("Lobby", "Attorney Online", 0));
        background->setText(QString());
        refresh->setText(QString());
        addtofav->setText(QString());
        connect->setText(QString());
        publicservers->setText(QString());
        favorites->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Lobby: public Ui_Lobby {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOBBY_H
