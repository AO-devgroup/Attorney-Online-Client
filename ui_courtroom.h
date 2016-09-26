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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
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
    QLineEdit *charpass;
    QLabel *defense_bar;
    QLabel *prosecution_bar;
    QPushButton *defplus;
    QPushButton *defminus;
    QPushButton *proplus;
    QPushButton *prominus;
    QLineEdit *musicsearch;
    QPushButton *ooc_toggle;
    QPushButton *realization;
    QPushButton *mute;
    QPushButton *witnesstestimony;
    QPushButton *crossexamination;
    QPushButton *reload_theme;
    QLabel *testimony;
    QComboBox *textcolor;
    QSlider *sfxslider;
    QSlider *musicslider;
    QSlider *blipslider;
    QLabel *musiclabel;
    QLabel *sfxlabel;
    QLabel *bliplabel;
    QListWidget *arealist;
    QLabel *areapreview;
    QLineEdit *areapassword;
    QLabel *deskpreview;
    QPushButton *callmod;
    QLabel *objectiongif;
    QCheckBox *prebox;
    QCheckBox *guardbox;
    QListWidget *mutelist;
    QLabel *muted;

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
        chatlog->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        chatlog->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        chatlog->setReadOnly(false);
        chatlog->setTextInteractionFlags(Qt::TextEditorInteraction);
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
        present->setEnabled(true);
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
        changecharacter->setGeometry(QRect(5, 390, 121, 23));
        charError = new QLabel(centralwidget);
        charError->setObjectName(QStringLiteral("charError"));
        charError->setGeometry(QRect(270, 50, 59, 15));
        musiclist = new QListWidget(centralwidget);
        new QListWidgetItem(musiclist);
        musiclist->setObjectName(QStringLiteral("musiclist"));
        musiclist->setGeometry(QRect(490, 342, 224, 326));
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
        ooc_master->setGeometry(QRect(80, 360, 60, 19));
        ooc_master->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: rgba( 255, 0, 0, 0% );\n"
"}\n"
""));
        ooc_master->setAutoDefault(false);
        ooc_master->setFlat(true);
        ooc_server = new QPushButton(centralwidget);
        ooc_server->setObjectName(QStringLiteral("ooc_server"));
        ooc_server->setGeometry(QRect(230, 370, 64, 19));
        ooc_server->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: rgba( 255, 0, 0, 0% );\n"
"}"));
        ooc_server->setFlat(true);
        charpass = new QLineEdit(centralwidget);
        charpass->setObjectName(QStringLiteral("charpass"));
        charpass->setGeometry(QRect(270, 10, 113, 22));
        defense_bar = new QLabel(centralwidget);
        defense_bar->setObjectName(QStringLiteral("defense_bar"));
        defense_bar->setGeometry(QRect(393, 323, 84, 14));
        defense_bar->setPixmap(QPixmap(QString::fromUtf8("../build-Attorney_Online_new-Desktop_Qt_5_7_0_GCC_64bit-Debug/base/misc/advocat.png")));
        prosecution_bar = new QLabel(centralwidget);
        prosecution_bar->setObjectName(QStringLiteral("prosecution_bar"));
        prosecution_bar->setGeometry(QRect(393, 340, 84, 14));
        prosecution_bar->setPixmap(QPixmap(QString::fromUtf8("../build-Attorney_Online_new-Desktop_Qt_5_7_0_GCC_64bit-Debug/base/misc/procuror.png")));
        defplus = new QPushButton(centralwidget);
        defplus->setObjectName(QStringLiteral("defplus"));
        defplus->setGeometry(QRect(477, 325, 9, 9));
        defminus = new QPushButton(centralwidget);
        defminus->setObjectName(QStringLiteral("defminus"));
        defminus->setGeometry(QRect(385, 325, 9, 9));
        proplus = new QPushButton(centralwidget);
        proplus->setObjectName(QStringLiteral("proplus"));
        proplus->setGeometry(QRect(477, 342, 9, 9));
        prominus = new QPushButton(centralwidget);
        prominus->setObjectName(QStringLiteral("prominus"));
        prominus->setGeometry(QRect(385, 342, 9, 9));
        musicsearch = new QLineEdit(centralwidget);
        musicsearch->setObjectName(QStringLiteral("musicsearch"));
        musicsearch->setGeometry(QRect(490, 319, 226, 23));
        ooc_toggle = new QPushButton(centralwidget);
        ooc_toggle->setObjectName(QStringLiteral("ooc_toggle"));
        ooc_toggle->setGeometry(QRect(580, 300, 133, 19));
        realization = new QPushButton(centralwidget);
        realization->setObjectName(QStringLiteral("realization"));
        realization->setGeometry(QRect(260, 330, 40, 40));
        mute = new QPushButton(centralwidget);
        mute->setObjectName(QStringLiteral("mute"));
        mute->setGeometry(QRect(305, 330, 40, 40));
        witnesstestimony = new QPushButton(centralwidget);
        witnesstestimony->setObjectName(QStringLiteral("witnesstestimony"));
        witnesstestimony->setGeometry(QRect(5, 345, 85, 42));
        crossexamination = new QPushButton(centralwidget);
        crossexamination->setObjectName(QStringLiteral("crossexamination"));
        crossexamination->setGeometry(QRect(95, 345, 85, 42));
        reload_theme = new QPushButton(centralwidget);
        reload_theme->setObjectName(QStringLiteral("reload_theme"));
        reload_theme->setGeometry(QRect(5, 415, 101, 23));
        testimony = new QLabel(centralwidget);
        testimony->setObjectName(QStringLiteral("testimony"));
        testimony->setGeometry(QRect(0, 0, 256, 192));
        textcolor = new QComboBox(centralwidget);
        textcolor->setObjectName(QStringLiteral("textcolor"));
        textcolor->setGeometry(QRect(390, 360, 79, 23));
        sfxslider = new QSlider(centralwidget);
        sfxslider->setObjectName(QStringLiteral("sfxslider"));
        sfxslider->setGeometry(QRect(310, 412, 160, 16));
        sfxslider->setMaximum(100);
        sfxslider->setSliderPosition(50);
        sfxslider->setOrientation(Qt::Horizontal);
        musicslider = new QSlider(centralwidget);
        musicslider->setObjectName(QStringLiteral("musicslider"));
        musicslider->setGeometry(QRect(310, 392, 160, 16));
        musicslider->setMaximum(100);
        musicslider->setSliderPosition(50);
        musicslider->setOrientation(Qt::Horizontal);
        musicslider->setInvertedAppearance(false);
        blipslider = new QSlider(centralwidget);
        blipslider->setObjectName(QStringLiteral("blipslider"));
        blipslider->setGeometry(QRect(310, 432, 160, 16));
        blipslider->setMaximum(100);
        blipslider->setSliderPosition(50);
        blipslider->setOrientation(Qt::Horizontal);
        musiclabel = new QLabel(centralwidget);
        musiclabel->setObjectName(QStringLiteral("musiclabel"));
        musiclabel->setGeometry(QRect(260, 390, 41, 16));
        sfxlabel = new QLabel(centralwidget);
        sfxlabel->setObjectName(QStringLiteral("sfxlabel"));
        sfxlabel->setGeometry(QRect(260, 410, 21, 16));
        bliplabel = new QLabel(centralwidget);
        bliplabel->setObjectName(QStringLiteral("bliplabel"));
        bliplabel->setGeometry(QRect(260, 430, 31, 16));
        arealist = new QListWidget(centralwidget);
        new QListWidgetItem(arealist);
        arealist->setObjectName(QStringLiteral("arealist"));
        arealist->setGeometry(QRect(266, 494, 224, 174));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::Base, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        arealist->setPalette(palette10);
        arealist->setFrameShape(QFrame::NoFrame);
        arealist->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        areapreview = new QLabel(centralwidget);
        areapreview->setObjectName(QStringLiteral("areapreview"));
        areapreview->setGeometry(QRect(5, 471, 256, 192));
        areapassword = new QLineEdit(centralwidget);
        areapassword->setObjectName(QStringLiteral("areapassword"));
        areapassword->setGeometry(QRect(266, 471, 224, 23));
        deskpreview = new QLabel(centralwidget);
        deskpreview->setObjectName(QStringLiteral("deskpreview"));
        deskpreview->setGeometry(QRect(5, 621, 256, 42));
        callmod = new QPushButton(centralwidget);
        callmod->setObjectName(QStringLiteral("callmod"));
        callmod->setGeometry(QRect(5, 440, 71, 23));
        objectiongif = new QLabel(centralwidget);
        objectiongif->setObjectName(QStringLiteral("objectiongif"));
        objectiongif->setGeometry(QRect(0, 0, 256, 192));
        prebox = new QCheckBox(centralwidget);
        prebox->setObjectName(QStringLiteral("prebox"));
        prebox->setGeometry(QRect(187, 347, 51, 21));
        guardbox = new QCheckBox(centralwidget);
        guardbox->setObjectName(QStringLiteral("guardbox"));
        guardbox->setGeometry(QRect(187, 365, 85, 21));
        mutelist = new QListWidget(centralwidget);
        mutelist->setObjectName(QStringLiteral("mutelist"));
        mutelist->setGeometry(QRect(260, 160, 231, 159));
        muted = new QLabel(centralwidget);
        muted->setObjectName(QStringLiteral("muted"));
        muted->setGeometry(QRect(0, 192, 258, 145));
        Courtroom->setCentralWidget(centralwidget);
        ooc_master->raise();
        ooc_server->raise();
        present->raise();
        charselect->raise();
        background->raise();
        chatlog->raise();
        takethat->raise();
        holdit->raise();
        objection->raise();
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
        musiclist->raise();
        oocserverchat->raise();
        oocchatname->raise();
        oocchatmessage->raise();
        oocmasterchat->raise();
        charname->raise();
        chattext->raise();
        charpass->raise();
        charError->raise();
        defense_bar->raise();
        prosecution_bar->raise();
        defplus->raise();
        defminus->raise();
        proplus->raise();
        prominus->raise();
        musicsearch->raise();
        ooc_toggle->raise();
        realization->raise();
        mute->raise();
        witnesstestimony->raise();
        crossexamination->raise();
        reload_theme->raise();
        testimony->raise();
        textcolor->raise();
        sfxslider->raise();
        musicslider->raise();
        blipslider->raise();
        musiclabel->raise();
        sfxlabel->raise();
        bliplabel->raise();
        arealist->raise();
        areapreview->raise();
        areapassword->raise();
        deskpreview->raise();
        callmod->raise();
        objectiongif->raise();
        prebox->raise();
        guardbox->raise();
        mutelist->raise();
        muted->raise();

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
        defense_bar->setText(QString());
        prosecution_bar->setText(QString());
        defplus->setText(QString());
        defminus->setText(QString());
        proplus->setText(QString());
        prominus->setText(QString());
        ooc_toggle->setText(QApplication::translate("Courtroom", "Master", 0));
        realization->setText(QString());
        mute->setText(QString());
        witnesstestimony->setText(QString());
        crossexamination->setText(QString());
        reload_theme->setText(QApplication::translate("Courtroom", "Reload theme", 0));
        testimony->setText(QString());
        textcolor->clear();
        textcolor->insertItems(0, QStringList()
         << QApplication::translate("Courtroom", "White", 0)
         << QApplication::translate("Courtroom", "Blue", 0)
         << QApplication::translate("Courtroom", "Green", 0)
         << QApplication::translate("Courtroom", "Orange", 0)
         << QApplication::translate("Courtroom", "Red", 0)
        );
        musiclabel->setText(QApplication::translate("Courtroom", "Music", 0));
        sfxlabel->setText(QApplication::translate("Courtroom", "Sfx", 0));
        bliplabel->setText(QApplication::translate("Courtroom", "Blips", 0));

        const bool __sortingEnabled1 = arealist->isSortingEnabled();
        arealist->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem1 = arealist->item(0);
        ___qlistwidgetitem1->setText(QApplication::translate("Courtroom", "bestarea", 0));
        arealist->setSortingEnabled(__sortingEnabled1);

        areapreview->setText(QString());
        deskpreview->setText(QString());
        callmod->setText(QApplication::translate("Courtroom", "Call mod", 0));
        objectiongif->setText(QString());
        prebox->setText(QApplication::translate("Courtroom", "Pre", 0));
        guardbox->setText(QApplication::translate("Courtroom", "Guard", 0));
        muted->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Courtroom: public Ui_Courtroom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURTROOM_H
