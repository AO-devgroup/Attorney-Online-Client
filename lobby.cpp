#include "lobby.h"

Lobby::Lobby(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lobby)
{
  ms_socket = new QTcpSocket(this);
  server_socket = new QTcpSocket(this);
  //in.setDevice(ms_socket);
  connect(ms_socket, &QTcpSocket::readyRead, this, &Lobby::handle_ms_packet);
  connect(server_socket, &QTcpSocket::readyRead, this, &Lobby::handle_server_packet);

  ui->setupUi(this);
}

void Lobby::setTheme()
{
  //literally everything breaks if you remove this
  LoadConfig(); //sets config.ini as a global variable !IMPORTANT!



  QString background_path = getImagePath("lobbybackground.png");
  QString refresh_path = getImagePath("refresh.png");
  QString addtofav_path = getImagePath("addtofav.png");
  QString connect_path = getImagePath("connect.png");
  QString publicservers_path = getImagePath("publicservers_selected.png");
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

  //
  //LoadFavorites();

  ui->favoritelist->hide();
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

  //you cant add favorites from favorites m8
  if (!public_servers_selected)
    return;

  //this means there is no selection
  if (int_selected_server == -1)
    return;

  server_type fav_server = m_server_list.at(int_selected_server);

  if (!favoritefile.open(QIODevice::WriteOnly | QIODevice::Append))
  {
    callError("failed to write in \"favorites.txt\"");
  }

  QTextStream out(&favoritefile);

  QString str_port = QString::number(fav_server.port);

  QString server_line = fav_server.ip + ":" + str_port + ":" + fav_server.name;

  out << server_line << '\n';

  //favoritefile.write(server_line);
  favoritefile.close();

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
  public_servers_selected = true;
  int_selected_server = -1;

  QString path_public = getImagePath("publicservers_selected.png");
  QString path_favorites = getImagePath("favorites.png");

  if (fileExists(path_public))
    ui->publicservers->setStyleSheet("border-image:url(" + path_public + ")");

    if (fileExists(path_favorites))
      ui->favorites->setStyleSheet("border-image:url(" + path_favorites + ")");

    ui->favoritelist->hide();
    ui->serverlist->show();
}

void Lobby::on_favorites_clicked()
{
  public_servers_selected = false;
  int_selected_server = -1;

  QString path_favorites = getImagePath("favorites_selected.png");
  QString path_public = getImagePath("publicservers.png");

  if (fileExists(path_favorites))
    ui->favorites->setStyleSheet("border-image:url(" + path_favorites + ")");

  if (fileExists(path_public))
    ui->publicservers->setStyleSheet("border-image:url(" + path_public + ")");

  LoadFavorites();

  ui->favoritelist->clear();

  for (server_type server : favoriteservers)
  {
    ui->favoritelist->addItem(server.name);
  }

  ui->serverlist->hide();
  ui->favoritelist->show();
}

void Lobby::on_serverlist_clicked(const QModelIndex &index)
{
  server_type f_server = m_server_list.at(index.row());

  ui->description->setPlainText(f_server.desc);

  int_selected_server = index.row();

  server_connect(f_server.ip, f_server.port);
}

void Lobby::on_favoritelist_clicked(const QModelIndex &index)
{
  server_type f_server = favoriteservers.at(index.row());

  if (f_server.name == "!MISCONFIGURED!")
    return;

  //ui->description->setPlainText(f_server.desc);

  int_selected_server = index.row();

  server_connect(f_server.ip, f_server.port);
}

void Lobby::LoadFavorites()
{


  if (fileExists((getBasePath() + "favorites.txt"), true))
    favoritefile.setFileName(getBasePath() + "favorites.txt");

  //legacy support, the new name is favorites.txt
  else if (fileExists((getBasePath() + "serverlist.txt"), true))
    favoritefile.setFileName(getBasePath() + "serverlist.txt");

  else
  {
    callError("could not find \"favorites.txt\" ");
    return;
  }

  if (!favoritefile.open(QIODevice::ReadOnly))
  {
    callError("failed to read \"favorites.txt\"");
  }
  QTextStream in(&favoritefile);

  QVector<server_type> temp_servers;

  for(int line_count{0}; ; ++line_count)
  {
    if (in.atEnd())
      break;

    QString line = in.readLine();
    QStringList line_contents = line.split(":");

    //we check if the line is valid first
    if (line_contents.size() == 3)
    {
      server_type serv;

      serv.name = line_contents.at(2);
      serv.ip = line_contents.at(0);
      serv.port = line_contents.at(1).toInt();

      temp_servers.insert(line_count, serv);

      favoriteservers = temp_servers;

      //favoriteservers.insert(line_count, serv);
    }

    else
    {
      QString str_line = QString::number(line_count + 1);

      callError("favorites.txt appears to be misconfigured on line " + str_line + ". Expected <ip>:<port>:<name> format.");

      server_type serv;

      serv.name = "!MISCONFIGURED!";
      serv.ip = "";
      serv.port = 0;

      temp_servers.insert(line_count, serv);

      favoriteservers = temp_servers;
    }

    if (in.atEnd())
      break;
  }

  favoritefile.close();
}

