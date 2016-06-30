#include "lobby.h"
#include "ui_lobby.h"
#include "config_handler.h"
#include "error_handler.h"
#include "courtroom.h"
#include "ui_courtroom.h"

Lobby::Lobby(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lobby)
{
    ui->setupUi(this);
    ui->background->setPixmap(QPixmap(getImagePath("lobbybackground.png")));
    ui->refresh->setStyleSheet("border-image:url(" + getImagePath("refresh.png") + ")");
    ui->addtofav->setStyleSheet("border-image:url(" + getImagePath("addtofav.png") + ")");
    ui->connect->setStyleSheet("border-image:url(" + getImagePath("connect.png") + ")");
    ui->publicservers->setStyleSheet("border-image:url(" + getImagePath("publicservers.png") + ")");
    ui->favorites->setStyleSheet("border-image:url(" + getImagePath("favorites.png") + ")");
    //connect(ui->addtofav, SIGNAL(click()), this, SLOT(openCourtroomWindow()));
}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::openCourtroomWindow()
{
   //mCourtroomWindow = new Ui::Courtroom(); // Be sure to destroy you window somewhere
   //mCourtroomWindow->show();
}

void Lobby::on_refresh_pressed()
{
    ui->refresh->setStyleSheet("border-image:url(" + getImagePath("refresh_pressed.png") + ")");
}

void Lobby::on_refresh_released()
{
    ui->refresh->setStyleSheet("border-image:url(" + getImagePath("refresh.png") + ")");
    callError("ur a fag"); //for debugging purposes
}

void Lobby::on_addtofav_pressed()
{
    ui->addtofav->setStyleSheet("border-image:url(" + getImagePath("addtofav_pressed.png") + ")");
}

void Lobby::on_addtofav_released()
{
    ui->addtofav->setStyleSheet("border-image:url(" + getImagePath("addtofav.png") + ")");
}

void Lobby::on_connect_pressed()
{
    ui->connect->setStyleSheet("border-image:url(" + getImagePath("connect_pressed.png") + ")");
}

void Lobby::on_connect_released()
{
    ui->connect->setStyleSheet("border-image:url(" + getImagePath("connect.png") + ")");
    mCourtroomWindow = new Courtroom(this);
    mCourtroomWindow->show();
}

void Lobby::on_publicservers_clicked()
{
    ui->publicservers->setStyleSheet("border-image:url(" + getImagePath("publicservers_selected.png") + ")");
    ui->favorites->setStyleSheet("border-image:url(" + getImagePath("favorites.png") + ")");
}

void Lobby::on_favorites_clicked()
{
    ui->favorites->setStyleSheet("border-image:url(" + getImagePath("favorites_selected.png") + ")");
    ui->publicservers->setStyleSheet("border-image:url(" + getImagePath("publicservers.png") + ")");
}
