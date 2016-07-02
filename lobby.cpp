#include "lobby.h"
#include "ui_lobby.h"
#include "courtroom.h"
#include "ui_courtroom.h"

#include "config_handler.h"
#include "error_handler.h"
#include "networking.h"


Lobby::Lobby(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lobby)
{
  ui->setupUi(this);

  //int id = QFontDatabase::addApplicationFont(":/resource/tahomabd.ttf");
  //QString family = QFontDatabase::applicationFontFamilies(id).at(0);
  //QFont tahomabd(family);

  ui->background->setPixmap(QPixmap(getImagePath("lobbybackground.png")));
  ui->refresh->setStyleSheet("border-image:url(" + getImagePath("refresh.png") + ")");
  ui->addtofav->setStyleSheet("border-image:url(" + getImagePath("addtofav.png") + ")");
  ui->connect->setStyleSheet("border-image:url(" + getImagePath("connect.png") + ")");
  ui->publicservers->setStyleSheet("border-image:url(" + getImagePath("publicservers_selected.png") + ")");
  ui->favorites->setStyleSheet("border-image:url(" + getImagePath("favorites.png") + ")");

  //tahomabd.setWeight(4);

  //ui->serverlist->setFont(tahomabd);


}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::openCourtroomWindow()
{
   //mCourtroomWindow = new Ui::Courtroom();
   //mCourtroomWindow->show();
}

void Lobby::on_refresh_pressed()
{
    ui->refresh->setStyleSheet("border-image:url(" + getImagePath("refresh_pressed.png") + ")");
}

void Lobby::on_refresh_released()
{
    ui->refresh->setStyleSheet("border-image:url(" + getImagePath("refresh.png") + ")");
    //callError("ur a fag");
    //call serverlist_refresh
    ui->serverlist->addItems(getServerList());
}

void Lobby::on_addtofav_pressed()
{
  QString image_path = getImagePath("addtofav_pressed.png");
  if (!fileExists(image_path))
    callError("Missing file: " + image_path);
  else
    ui->addtofav->setStyleSheet("border-image:url(" + image_path + ")");

}

void Lobby::on_addtofav_released()
{
    ui->addtofav->setStyleSheet("border-image:url(" + getImagePath("addtofav.png") + ")");
    ui->serverlist->addItem("OAH");
}

void Lobby::on_connect_pressed()
{
    ui->connect->setStyleSheet("border-image:url(" + getImagePath("connect_pressed.png") + ")");
}

void Lobby::on_connect_released()
{
    ui->connect->setStyleSheet("border-image:url(" + getImagePath("connect.png") + ")");
    mCourtroomWindow = new Courtroom(this);
    mCourtroomWindow->setWindowModality(Qt::NonModal);
    mCourtroomWindow->show();
    this->hide();
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
