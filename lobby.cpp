#include "lobby.h"

Lobby::Lobby(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lobby)
{


  ui->setupUi(this);
}

void Lobby::setTheme()
{
  /*
  QString default_path = getBasePath() + "themes/default/";

  QString background_path = (g_theme_path + "lobbybackground.png");
  QString d_background_path = (default_path + "lobbybackground.png");

  QString refresh_path = (g_theme_path + "refresh.png");
  QString d_refresh_path = (default_path + "refresh.png");

  QString addtofav_path = (g_theme_path + "addtofav.png");
  QString d_addtofav_path = (default_path + "addtofav.png");

  QString connect_path = (g_theme_path + "connect.png");
  QString publicservers_path = (g_theme_path + "publicservers_selected.png");
  QString favorites_path = (g_theme_path + "favorites.png");

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

  */

  ui->background->setPixmap(get_image_path("lobbybackground.png"));
  ui->refresh->setStyleSheet("border-image:url(" + get_image_path("refresh.png") + ")");
  ui->addtofav->setStyleSheet("border-image:url(" + get_image_path("addtofav.png") + ")");
  ui->connect->setStyleSheet("border-image:url(" + get_image_path("connect.png") + ")");
  ui->publicservers->setStyleSheet("border-image:url(" + get_image_path("publicservers_selected.png") + ")");
  ui->favorites->setStyleSheet("border-image:url(" + get_image_path("favorites.png") + ")");
  ui->about->setStyleSheet("border-image:url(" + get_image_path("about.png") +")");

  ui->favoritelist->hide();

  //callError("Sample text");
}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::on_refresh_pressed()
{
  ui->refresh->setStyleSheet("border-image:url(" + get_image_path("refresh_pressed.png") +")");
}

void Lobby::on_refresh_released()
{
  ui->refresh->setStyleSheet("border-image:url(" + get_image_path("refresh.png") + ")");
}

void Lobby::on_addtofav_pressed()
{
  ui->addtofav->setStyleSheet("border-image:url(" + get_image_path("addtofav_pressed.png") + ")");
}

void Lobby::on_addtofav_released()
{
  ui->addtofav->setStyleSheet("border-image:url(" + get_image_path("addtofav.png") + ")");

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
  ui->connect->setStyleSheet("border-image:url(" + get_image_path("connect_pressed.png") + ")");
}

void Lobby::on_connect_released()
{
  ui->connect->setStyleSheet("border-image:url(" + get_image_path("connect.png") + ")");

  enter_server_requested();
}

void Lobby::on_publicservers_clicked()
{
  public_servers_selected = true;
  int_selected_server = -1;

  ui->publicservers->setStyleSheet("border-image:url(" + get_image_path("publicservers_selected.png") + ")");
  ui->favorites->setStyleSheet("border-image:url(" + get_image_path("favorites.png") + ")");

  ui->favoritelist->hide();
  ui->serverlist->show();
}

void Lobby::on_favorites_clicked()
{
  public_servers_selected = false;
  int_selected_server = -1;

  ui->publicservers->setStyleSheet("border-image:url(" + get_image_path("publicservers.png") + ")");
  ui->favorites->setStyleSheet("border-image:url(" + get_image_path("favorites_selected.png") + ")");

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
  //server_disconnect_requested();

  ui->onlinestatus->setText("Offline");

  server_type f_server = m_server_list.at(index.row());

  ui->description->setPlainText(f_server.desc);

  int_selected_server = index.row();

  server_connection_requested(f_server.ip, f_server.port);
}

void Lobby::on_favoritelist_clicked(const QModelIndex &index)
{
  ui->onlinestatus->setText("Offline");

  server_type f_server = favoriteservers.at(index.row());

  if (f_server.name == "!MISCONFIGURED!")
    return;

  //ui->description->setPlainText(f_server.desc);

  int_selected_server = index.row();

  server_connection_requested(f_server.ip, f_server.port);
}

void Lobby::on_chatmessage_returnPressed()
{
  QString name = ui->chatname->text();
  QString message = ui->chatmessage->text();
  QString packet = "CT#" + name.replace("#", "<num>").replace("%", "<percent>") + "#" +
      message.replace("#", "<num>").replace("%", "<percent>") + "#%";

  //no you cant send empty messages
  if ((name == "") || (message == ""))
    return;

  ms_message_requested(packet);
  ui->chatmessage->clear();

}

void Lobby::handle_ms_message(QString message)
{
  ui->chatbox->appendPlainText(message);
}

void Lobby::update_server_list(QVector<server_type> &server_list)
{
  ui->serverlist->clear();
  m_server_list.clear();

  for (int n_server = 0; n_server < server_list.size() ; ++n_server)
  {
    QString server = server_list.at(n_server).name;
    m_server_list.insert(n_server, server_list.at(n_server));
    ui->serverlist->addItem(server);
  }
}

void Lobby::update_onlinestatus(QString players_online, QString max_players)
{
  ui->onlinestatus->setText("Online: " + players_online + "/" + max_players);
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
      //QString str_line = QString::number(line_count + 1);

      //bad servers already show up as !MISCONFIGURED! we dont need this dumb error >:v(
      //callError("favorites.txt appears to be misconfigured on line " + str_line + ". Expected <ip>:<port>:<name> format.");

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

void Lobby::handle_server_entry()
{
  this->hide();
}

void Lobby::handle_server_exit()
{
  this->show();
}

void Lobby::on_about_clicked()
{
  QMessageBox *msgBox = new QMessageBox;
  QString f_release = QString::number(RELEASE);
  QString f_major = QString::number(MAJOR_VERSION);
  QString f_minor = QString::number(MINOR_VERSION);


  msgBox->setText("Client version: " + f_release + "." + f_major + "." + f_minor + "\n"
                  "\n"
                  "Contributors:\n"
                  "OmniTroid\n"
                  "stonedDiscord\n"
                  "Alex\n"
                  "Unishred\n"
                  "Argoneus\n"
                  "Lupadim\n"
                  "Ruekasu\n"
                  "Draxirch\n"
                  "Fiercy\n"
                  "Cronnicossy\n"
                  "\n"
                  "Original concept:\n"
                  "FanatSors\n"
                  "\n"
                  "All characters, images, names, songs and sound effects belong to their respective owners.");
  msgBox->setWindowTitle("About");
  msgBox->setWindowModality(Qt::NonModal);
  msgBox->show();
}

void Lobby::closeEvent (QCloseEvent *event)
{
  //this is just to prevent those annoying "unused parameter" errors
  event->accept();

  request_quit();
}
