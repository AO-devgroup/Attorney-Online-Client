/********************************************************************************
** Form generated from reading UI file 'courtroom.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURTROOM_H
#define UI_COURTROOM_H

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

class Ui_Courtroom
{
public:
    QWidget *centralwidget;
    QLabel *background;
    QPushButton *objection;
    QPlainTextEdit *chatlog;
    QPushButton *holdit;
    QPushButton *takethat;
    QLabel *playingarea;
    QPushButton *present;
    QLineEdit *chatLine;
    QLabel *desk;
    QLabel *playingbackground;
    QLabel *chatbubble;
    QLabel *charselect;
    QPushButton *spectator;
    QLabel *charselector;
    QPushButton *charselect_left;
    QPushButton *charselect_right;
    QPushButton *changecharacter;
    QLabel *charError;
    QListWidget *musiclist;
    QPlainTextEdit *oocserverchat;
    QPlainTextEdit *oocmasterchat;
    QLineEdit *oocchatname;
    QLineEdit *oocchatmessage;
    QLabel *charname;
    QPlainTextEdit *chattext;
    QPushButton *ooc_master;
    QPushButton *ooc_server;

    void setupUi(QMainWindow *Courtroom)
    {
        if (Courtroom->objectName().isEmpty())
            Courtroom->setObjectName(QStringLiteral("Courtroom"));
        Courtroom->resize(714, 668);
        Courtroom->setMinimumSize(QSize(256, 192));
        Courtroom->setMaximumSize(QSize(714, 668));
        QIcon icon;
        icon.addFile(QStringLiteral(":/resource/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        Courtroom->setWindowIcon(icon);
        centralwidget = new QWidget(Courtroom);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        background = new QLabel(centralwidget);
        background->setObjectName(QStringLiteral("background"));
        background->setGeometry(QRect(0, 0, 714, 668));
        background->setPixmap(QPixmap(QString::fromUtf8("../build-Attorney_Online_new-Desktop_Qt_5_7_0_GCC_64bit-Debug/base/themes/default/courtroombackground.png")));
        objection = new QPushButton(centralwidget);
        objection->setObjectName(QStringLiteral("objection"));
        objection->setGeometry(QRect(90, 312, 76, 28));
        objection->setFlat(false);
        chatlog = new QPlainTextEdit(centralwidget);
        chatlog->setObjectName(QStringLiteral("chatlog"));
        chatlog->setGeometry(QRect(260, 0, 231, 319));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 0));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush);
        QBrush brush2(QColor(190, 190, 190, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        QBrush brush3(QColor(239, 235, 231, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        chatlog->setPalette(palette);
        chatlog->setAutoFillBackground(false);
        chatlog->setFrameShape(QFrame::NoFrame);
        chatlog->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        chatlog->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        chatlog->setReadOnly(true);
        chatlog->setTextInteractionFlags(Qt::NoTextInteraction);
        holdit = new QPushButton(centralwidget);
        holdit->setObjectName(QStringLiteral("holdit"));
        holdit->setGeometry(QRect(10, 312, 76, 28));
        QPalette palette1;
        QBrush brush4(QColor(48, 140, 198, 0));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush4);
        palette1.setBrush(QPalette::Active, QPalette::HighlightedText, brush);
        QBrush brush5(QColor(217, 140, 255, 0));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Link, brush5);
        QBrush brush6(QColor(149, 117, 255, 0));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::LinkVisited, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Link, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::LinkVisited, brush6);
        QBrush brush7(QColor(145, 141, 126, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Link, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::LinkVisited, brush6);
        holdit->setPalette(palette1);
        holdit->setFlat(false);
        takethat = new QPushButton(centralwidget);
        takethat->setObjectName(QStringLiteral("takethat"));
        takethat->setGeometry(QRect(170, 312, 76, 28));
        takethat->setFlat(false);
        playingarea = new QLabel(centralwidget);
        playingarea->setObjectName(QStringLiteral("playingarea"));
        playingarea->setGeometry(QRect(0, 0, 256, 192));
        present = new QPushButton(centralwidget);
        present->setObjectName(QStringLiteral("present"));
        present->setGeometry(QRect(171, 626, 158, 41));
        present->setFlat(false);
        chatLine = new QLineEdit(centralwidget);
        chatLine->setObjectName(QStringLiteral("chatLine"));
        chatLine->setGeometry(QRect(0, 192, 256, 23));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Light, brush);
        QBrush brush8(QColor(99, 214, 255, 0));
        brush8.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush8);
        QBrush brush9(QColor(38, 134, 198, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Highlight, brush9);
        palette2.setBrush(QPalette::Active, QPalette::Link, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush8);
        palette2.setBrush(QPalette::Inactive, QPalette::Highlight, brush9);
        palette2.setBrush(QPalette::Inactive, QPalette::Link, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Highlight, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Link, brush1);
        chatLine->setPalette(palette2);
        chatLine->setFrame(false);
        desk = new QLabel(centralwidget);
        desk->setObjectName(QStringLiteral("desk"));
        desk->setGeometry(QRect(0, 150, 256, 42));
        playingbackground = new QLabel(centralwidget);
        playingbackground->setObjectName(QStringLiteral("playingbackground"));
        playingbackground->setGeometry(QRect(0, 0, 256, 192));
        chatbubble = new QLabel(centralwidget);
        chatbubble->setObjectName(QStringLiteral("chatbubble"));
        chatbubble->setGeometry(QRect(0, 114, 256, 78));
        charselect = new QLabel(centralwidget);
        charselect->setObjectName(QStringLiteral("charselect"));
        charselect->setGeometry(QRect(0, 0, 714, 668));
        charselect->setPixmap(QPixmap(QString::fromUtf8("../build-Attorney_Online_new-Desktop_Qt_5_7_0_GCC_64bit-Debug/base/themes/default/charselect_background.png")));
        spectator = new QPushButton(centralwidget);
        spectator->setObjectName(QStringLiteral("spectator"));
        spectator->setGeometry(QRect(317, 640, 80, 23));
        charselector = new QLabel(centralwidget);
        charselector->setObjectName(QStringLiteral("charselector"));
        charselector->setGeometry(QRect(370, 260, 62, 62));
        charselect_left = new QPushButton(centralwidget);
        charselect_left->setObjectName(QStringLiteral("charselect_left"));
        charselect_left->setGeometry(QRect(2, 325, 20, 20));
        charselect_right = new QPushButton(centralwidget);
        charselect_right->setObjectName(QStringLiteral("charselect_right"));
        charselect_right->setGeometry(QRect(691, 325, 20, 20));
        changecharacter = new QPushButton(centralwidget);
        changecharacter->setObjectName(QStringLiteral("changecharacter"));
        changecharacter->setGeometry(QRect(250, 327, 131, 23));
        charError = new QLabel(centralwidget);
        charError->setObjectName(QStringLiteral("charError"));
        charError->setGeometry(QRect(270, 50, 59, 15));
        musiclist = new QListWidget(centralwidget);
        new QListWidgetItem(musiclist);
        musiclist->setObjectName(QStringLiteral("musiclist"));
        musiclist->setGeometry(QRect(490, 340, 224, 329));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        musiclist->setPalette(palette3);
        musiclist->setFrameShape(QFrame::NoFrame);
        musiclist->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        oocserverchat = new QPlainTextEdit(centralwidget);
        oocserverchat->setObjectName(QStringLiteral("oocserverchat"));
        oocserverchat->setGeometry(QRect(490, 1, 224, 277));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        oocserverchat->setPalette(palette4);
        oocserverchat->setFrameShape(QFrame::NoFrame);
        oocserverchat->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        oocserverchat->setReadOnly(true);
        oocmasterchat = new QPlainTextEdit(centralwidget);
        oocmasterchat->setObjectName(QStringLiteral("oocmasterchat"));
        oocmasterchat->setGeometry(QRect(490, 1, 224, 277));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Base, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        oocmasterchat->setPalette(palette5);
        oocmasterchat->setFrameShape(QFrame::NoFrame);
        oocmasterchat->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        oocmasterchat->setReadOnly(true);
        oocchatname = new QLineEdit(centralwidget);
        oocchatname->setObjectName(QStringLiteral("oocchatname"));
        oocchatname->setGeometry(QRect(492, 300, 85, 19));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(oocchatname->sizePolicy().hasHeightForWidth());
        oocchatname->setSizePolicy(sizePolicy);
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Base, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        oocchatname->setPalette(palette6);
        QFont font;
        font.setPointSize(9);
        oocchatname->setFont(font);
        oocchatname->setFrame(false);
        oocchatmessage = new QLineEdit(centralwidget);
        oocchatmessage->setObjectName(QStringLiteral("oocchatmessage"));
        oocchatmessage->setGeometry(QRect(492, 281, 222, 19));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Base, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        oocchatmessage->setPalette(palette7);
        QFont font1;
        font1.setPointSize(10);
        oocchatmessage->setFont(font1);
        oocchatmessage->setFrame(false);
        charname = new QLabel(centralwidget);
        charname->setObjectName(QStringLiteral("charname"));
        charname->setGeometry(QRect(6, 113, 59, 15));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette8.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette8.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        charname->setPalette(palette8);
        QFont font2;
        font2.setPointSize(8);
        charname->setFont(font2);
        chattext = new QPlainTextEdit(centralwidget);
        chattext->setObjectName(QStringLiteral("chattext"));
        chattext->setGeometry(QRect(3, 132, 250, 60));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette9.setBrush(QPalette::Active, QPalette::Base, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette9.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette9.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        chattext->setPalette(palette9);
        chattext->setFrameShape(QFrame::NoFrame);
        chattext->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        chattext->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        chattext->setReadOnly(true);
        chattext->setTextInteractionFlags(Qt::NoTextInteraction);
        ooc_master = new QPushButton(centralwidget);
        ooc_master->setObjectName(QStringLiteral("ooc_master"));
        ooc_master->setGeometry(QRect(580, 300, 60, 19));
        ooc_master->setFlat(true);
        ooc_server = new QPushButton(centralwidget);
        ooc_server->setObjectName(QStringLiteral("ooc_server"));
        ooc_server->setGeometry(QRect(646, 300, 64, 19));
        ooc_server->setFlat(true);
        Courtroom->setCentralWidget(centralwidget);
        charselect->raise();
        background->raise();
        chatlog->raise();
        takethat->raise();
        holdit->raise();
        objection->raise();
        present->raise();
        chatLine->raise();
        playingbackground->raise();
        playingarea->raise();
        desk->raise();
        chatbubble->raise();
        spectator->raise();
        charselector->raise();
        charselect_left->raise();
        charselect_right->raise();
        changecharacter->raise();
        charError->raise();
        musiclist->raise();
        oocserverchat->raise();
        oocchatname->raise();
        oocchatmessage->raise();
        oocmasterchat->raise();
        charname->raise();
        chattext->raise();
        ooc_master->raise();
        ooc_server->raise();

        retranslateUi(Courtroom);

        ooc_master->setDefault(false);


        QMetaObject::connectSlotsByName(Courtroom);
    } // setupUi

    void retranslateUi(QMainWindow *Courtroom)
    {
        Courtroom->setWindowTitle(QApplication::translate("Courtroom", "Attorney Online", 0));
        background->setText(QString());
        objection->setText(QString());
        chatlog->setPlainText(QString());
        holdit->setText(QString());
        takethat->setText(QString());
        playingarea->setText(QString());
        present->setText(QString());
        desk->setText(QString());
        playingbackground->setText(QString());
        chatbubble->setText(QString());
        charselect->setText(QString());
        spectator->setText(QApplication::translate("Courtroom", "Spectator", 0));
        charselector->setText(QString());
        charselect_left->setText(QString());
        charselect_right->setText(QString());
        changecharacter->setText(QApplication::translate("Courtroom", "Change character", 0));
        charError->setText(QString());

        const bool __sortingEnabled = musiclist->isSortingEnabled();
        musiclist->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = musiclist->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Courtroom", "u wot m8", 0));
        musiclist->setSortingEnabled(__sortingEnabled);

        oocchatname->setPlaceholderText(QApplication::translate("Courtroom", "Name", 0));
        charname->setText(QString());
        ooc_master->setText(QApplication::translate("Courtroom", "Master", 0));
        ooc_server->setText(QApplication::translate("Courtroom", "Server", 0));
    } // retranslateUi

};

namespace Ui {
    class Courtroom: public Ui_Courtroom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURTROOM_H
