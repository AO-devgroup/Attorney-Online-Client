#include "lobby.h"

Lobby::Lobby(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lobby)
{
  ui->setupUi(this);

  //int id = QFontDatabase::addApplicationFont(":/resource/tahomabd.ttf");
  //QString family = QFontDatabase::applicationFontFamilies(id).at(0);
  //QFont tahomabd(family);

  //tahomabd.setWeight(4);

  //ui->serverlist->setFont(tahomabd);


}

void Lobby::setTheme()
{
  QString background_path = getImagePath("lobbybackground.png");
  QString refresh_path = getImagePath("refresh.png");
  QString addtofav_path = getImagePath("addtofav.png");
  QString connect_path = getImagePath("connect.png");
  QString publicservers_path = getImagePath("publicservers.png");
  QString favorites_path = getImagePath("favorites.png");

  if (fileExists(background_path))
    ui->background->setPixmap(QPixmap(background_path));

  if (fileExists(refresh_path))
    ui->refresh->setStyleSheet("border-image:url(" + refresh_path + ")");

  if (fileExists(addtofav_path))
    ui->addtofav->setStyleSheet("border-image:url(" + addtofav_path + ")");

  if (fileExists(connect_path))
    ui->connect->setStyleSheet("border-image:url(" + connect_path + ")");

  if (fileExists(publicservers_path))
    ui->publicservers->setStyleSheet("border-image:url(" + publicservers_path + ")");

  if (fileExists(favorites_path))
    ui->favorites->setStyleSheet("border-image:url(" + favorites_path + ")");
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
  QString path = getImagePath("refresh_pressed.png");

  if (fileExists(path))
    ui->refresh->setStyleSheet("border-image:url(" + path + ")");
}

void Lobby::on_refresh_released()
{
  QString path = getImagePath("refresh.png");

    ui->refresh->setStyleSheet("border-image:url(" + path + ")");

    ui->serverlist->clear();
    ui->serverlist->addItems(getServerList());
}

void Lobby::on_addtofav_pressed()
{
  QString path = getImagePath("addtofav_pressed.png");

  if (fileExists(path))
      ui->addtofav->setStyleSheet("border-image:url(" + path + ")");
}

void Lobby::on_addtofav_released()
{
  QString path = getImagePath("addtofav.png");

  if (fileExists(path))
    ui->addtofav->setStyleSheet("border-image:url(" + path + ")");
}

void Lobby::on_connect_pressed()
{
  QString path = getImagePath("connect_pressed.png");

  if (fileExists(path))
    ui->connect->setStyleSheet("border-image:url(" + path + ")");
}

void Lobby::on_connect_released()
{
  QString path = getImagePath("connect.png");

  if (fileExists(path))
  {
    ui->connect->setStyleSheet("border-image:url(" + path + ")");
    mCourtroomWindow = new Courtroom(this);
    mCourtroomWindow->setWindowModality(Qt::NonModal);
    mCourtroomWindow->show();
    this->hide();
  }

}

void Lobby::on_publicservers_clicked()
{
  QString path_public = getImagePath("publicservers_selected.png");
  QString path_favorites = getImagePath("favorites.png");

  if (fileExists(path_public))
    ui->publicservers->setStyleSheet("border-image:url(" + path_public + ")");

    if (fileExists(path_favorites))
      ui->favorites->setStyleSheet("border-image:url(" + path_favorites + ")");
}

void Lobby::on_favorites_clicked()
{
  QString path_favorites = getImagePath("favorites_selected.png");
  QString path_public = getImagePath("publicservers.png");

  if (fileExists(path_favorites))
    ui->favorites->setStyleSheet("border-image:url(" + path_favorites + ")");

    if (fileExists(path_public))
      ui->publicservers->setStyleSheet("border-image:url(" + path_public + ")");
}
