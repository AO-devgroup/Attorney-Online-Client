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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
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
    QListWidget *chatbox;
    QLineEdit *chatname;
    QLineEdit *chatmessage;
    QPlainTextEdit *description;

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
        chatbox = new QListWidget(centralwidget);
        chatbox->setObjectName(QStringLiteral("chatbox"));
        chatbox->setGeometry(QRect(2, 445, 515, 198));
        QPalette palette1;
        QBrush brush2(QColor(111, 255, 116, 0));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        chatbox->setPalette(palette1);
        QFont font1;
        font1.setPointSize(8);
        chatbox->setFont(font1);
        chatbox->setFocusPolicy(Qt::NoFocus);
        chatbox->setFrameShape(QFrame::NoFrame);
        chatbox->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        chatbox->setSelectionMode(QAbstractItemView::NoSelection);
        chatbox->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        chatbox->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        chatbox->setWordWrap(true);
        chatname = new QLineEdit(centralwidget);
        chatname->setObjectName(QStringLiteral("chatname"));
        chatname->setGeometry(QRect(3, 646, 85, 19));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(chatname->sizePolicy().hasHeightForWidth());
        chatname->setSizePolicy(sizePolicy);
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        chatname->setPalette(palette2);
        QFont font2;
        font2.setPointSize(9);
        chatname->setFont(font2);
        chatname->setFrame(false);
        chatmessage = new QLineEdit(centralwidget);
        chatmessage->setObjectName(QStringLiteral("chatmessage"));
        chatmessage->setGeometry(QRect(93, 646, 424, 19));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        chatmessage->setPalette(palette3);
        QFont font3;
        font3.setPointSize(10);
        chatmessage->setFont(font3);
        chatmessage->setFrame(false);
        description = new QPlainTextEdit(centralwidget);
        description->setObjectName(QStringLiteral("description"));
        description->setGeometry(QRect(340, 110, 171, 241));
        QPalette palette4;
        QBrush brush3(QColor(255, 255, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipText, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush3);
        QBrush brush4(QColor(190, 190, 190, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush3);
        description->setPalette(palette4);
        description->setReadOnly(true);
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
        chatname->setPlaceholderText(QApplication::translate("Lobby", "Name", 0));
        description->setPlainText(QString());
    } // retranslateUi

};

namespace Ui {
    class Lobby: public Ui_Lobby {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOBBY_H
