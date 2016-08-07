#include "lobby.h"

Lobby::Lobby(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lobby)
{
  ms_socket = new QTcpSocket(this);
  //in.setDevice(ms_socket);
  connect(ms_socket, &QTcpSocket::readyRead, this, &Lobby::handle_ms_packet);

  ui->setupUi(this);
}

void Lobby::setTheme()
{

  LoadConfig(); //sets config.ini as a global variable !IMPORTANT!
                //literally everything breaks if you remove this

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

  //ui->serverlist->clear();
  //ui->serverlist->addItems(getServerList());
  requestAllServers();
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

  pingMaster();
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
  }

  if(!court_exists)
  {
    court_exists = true;
    mCourtroomWindow = new Courtroom(this);
    //mCourtroomWindow->setTheme();
    //mCourtroomWindow->char_select_list = getCharSelectList();
    mCourtroomWindow->setCharSelect();
    //mCourtroomWindow->setChar();
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
