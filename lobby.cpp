#include "lobby.h"
#include "ui_lobby.h"
#include "config_handler.h"
#include "error_handler.h"

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
}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::on_refresh_pressed()
{
    ui->refresh->setStyleSheet("border-image:url(" + getImagePath("refresh_onclick.png") + ")");
}

void Lobby::on_refresh_released()
{
    ui->refresh->setStyleSheet("border-image:url(" + getImagePath("refresh.png") + ")");
}

void Lobby::on_addtofav_pressed()
{
    ui->addtofav->setStyleSheet("border-image:url(" + getImagePath("addtofav_onclick.png") + ")");
}

void Lobby::on_addtofav_released()
{
    ui->addtofav->setStyleSheet("border-image:url(" + getImagePath("addtofav.png") + ")");
}

void Lobby::on_connect_pressed()
{
    ui->connect->setStyleSheet("border-image:url(" + getImagePath("connect_onclick.png") + ")");
}

void Lobby::on_connect_released()
{
    ui->connect->setStyleSheet("border-image:url(" + getImagePath("connect.png") + ")");
    callError("ur a fag");
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
