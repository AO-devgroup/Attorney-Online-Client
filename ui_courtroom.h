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
    QPushButton *emote1;
    QPushButton *emote2;
    QPushButton *emote3;
    QPushButton *emote4;
    QPushButton *emote5;
    QPushButton *emote6;
    QPushButton *emote7;
    QPushButton *emote8;
    QPushButton *emote9;
    QPushButton *emote10;
    QPushButton *emote_right;
    QPushButton *emote_left;
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
        chatlog->setGeometry(QRect(270, 0, 211, 311));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 0));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush);
        chatlog->setPalette(palette);
        chatlog->setAutoFillBackground(false);
        holdit = new QPushButton(centralwidget);
        holdit->setObjectName(QStringLiteral("holdit"));
        holdit->setGeometry(QRect(10, 312, 76, 28));
        QPalette palette1;
        QBrush brush1(QColor(48, 140, 198, 0));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush1);
        palette1.setBrush(QPalette::Active, QPalette::HighlightedText, brush);
        QBrush brush2(QColor(217, 140, 255, 0));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Link, brush2);
        QBrush brush3(QColor(149, 117, 255, 0));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::LinkVisited, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Link, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::LinkVisited, brush3);
        QBrush brush4(QColor(145, 141, 126, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Link, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::LinkVisited, brush3);
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
        QBrush brush5(QColor(99, 214, 255, 0));
        brush5.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush5);
        QBrush brush6(QColor(239, 235, 231, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Highlight, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush5);
        palette2.setBrush(QPalette::Inactive, QPalette::Highlight, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Highlight, brush4);
        chatLine->setPalette(palette2);
        emote1 = new QPushButton(centralwidget);
        emote1->setObjectName(QStringLiteral("emote1"));
        emote1->setGeometry(QRect(10, 219, 40, 40));
        emote1->setFlat(false);
        emote2 = new QPushButton(centralwidget);
        emote2->setObjectName(QStringLiteral("emote2"));
        emote2->setGeometry(QRect(59, 219, 40, 40));
        emote3 = new QPushButton(centralwidget);
        emote3->setObjectName(QStringLiteral("emote3"));
        emote3->setGeometry(QRect(108, 219, 40, 40));
        emote4 = new QPushButton(centralwidget);
        emote4->setObjectName(QStringLiteral("emote4"));
        emote4->setGeometry(QRect(157, 219, 40, 40));
        emote5 = new QPushButton(centralwidget);
        emote5->setObjectName(QStringLiteral("emote5"));
        emote5->setGeometry(QRect(206, 219, 40, 40));
        emote6 = new QPushButton(centralwidget);
        emote6->setObjectName(QStringLiteral("emote6"));
        emote6->setGeometry(QRect(10, 266, 40, 40));
        emote7 = new QPushButton(centralwidget);
        emote7->setObjectName(QStringLiteral("emote7"));
        emote7->setGeometry(QRect(59, 266, 40, 40));
        emote8 = new QPushButton(centralwidget);
        emote8->setObjectName(QStringLiteral("emote8"));
        emote8->setGeometry(QRect(108, 266, 40, 40));
        emote9 = new QPushButton(centralwidget);
        emote9->setObjectName(QStringLiteral("emote9"));
        emote9->setGeometry(QRect(157, 266, 40, 40));
        emote10 = new QPushButton(centralwidget);
        emote10->setObjectName(QStringLiteral("emote10"));
        emote10->setGeometry(QRect(206, 266, 40, 40));
        emote_right = new QPushButton(centralwidget);
        emote_right->setObjectName(QStringLiteral("emote_right"));
        emote_right->setGeometry(QRect(236, 253, 20, 20));
        emote_left = new QPushButton(centralwidget);
        emote_left->setObjectName(QStringLiteral("emote_left"));
        emote_left->setGeometry(QRect(0, 253, 20, 20));
        desk = new QLabel(centralwidget);
        desk->setObjectName(QStringLiteral("desk"));
        desk->setGeometry(QRect(0, 149, 256, 42));
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
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush6);
        musiclist->setPalette(palette3);
        musiclist->setFrameShape(QFrame::NoFrame);
        musiclist->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        Courtroom->setCentralWidget(centralwidget);
        charselect->raise();
        background->raise();
        chatlog->raise();
        takethat->raise();
        holdit->raise();
        objection->raise();
        present->raise();
        chatLine->raise();
        emote1->raise();
        emote2->raise();
        emote3->raise();
        emote4->raise();
        emote5->raise();
        emote6->raise();
        emote7->raise();
        emote8->raise();
        emote9->raise();
        emote10->raise();
        emote_right->raise();
        emote_left->raise();
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

        retranslateUi(Courtroom);

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
        emote1->setText(QString());
        emote2->setText(QString());
        emote3->setText(QString());
        emote4->setText(QString());
        emote5->setText(QString());
        emote6->setText(QString());
        emote7->setText(QString());
        emote8->setText(QString());
        emote9->setText(QString());
        emote10->setText(QString());
        emote_right->setText(QString());
        emote_left->setText(QString());
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

    } // retranslateUi

};

namespace Ui {
    class Courtroom: public Ui_Courtroom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURTROOM_H
