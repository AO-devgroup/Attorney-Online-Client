#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>
#include <QFont>
#include <QString>
#include <QtNetwork>
#include <QDataStream>
#include <QSizePolicy>

#include "ui_lobby.h"
#include "courtroom.h"
#include "ui_courtroom.h"

#include "config_handler.h"
#include "error_handler.h"
#include "networking.h"
#include "datatypes.h"

namespace Ui {
class Lobby;
}

class Lobby : public QMainWindow
{
  Q_OBJECT

public:
  explicit Lobby(QWidget *parent = 0);
  Courtroom *mCourtroomWindow;
  void setTheme();

  void lookupMaster();
  void pingMaster();
  void connectMaster();
  //QHostAddress msIP;
  QString msHOST = "master.aceattorneyonline.com";
  int msPORT = 27016;
  QTcpSocket *ms_socket;
  QTcpSocket *server_socket;
  void refreshServerList();
  bool master_connected = false;
  bool server_connected = false;
  void requestAllServers();
  QVector<server_type> m_server_list;
  void server_connect(QString ip, int port);
  int int_selected_server = -1;
  void establish_connection();

  QFile favoritefile;

  //true is public servers selected, false is favorites
  bool public_servers_selected = true;
  QVector<server_type> favoriteservers;
  void LoadFavorites();

  int charlist_size;
  int evidence_size;
  int musiclist_size;

  bool array_sizes_set = false;

  //QStringList m_server_list;
  //QDataStream in;

  ~Lobby();

public slots:

  //void lookedUp(QHostInfo);

  void handle_ms_packet();

  void handle_server_packet();

  void ms_connection_established();

  void ms_failed_to_connect();

  void server_disconnected();

private slots:
  void on_refresh_pressed();

  void on_refresh_released();

  void on_addtofav_pressed();

  void on_addtofav_released();

  void on_connect_pressed();

  void on_connect_released();

  void on_publicservers_clicked();

  void on_favorites_clicked();

  void on_chatmessage_returnPressed();

  void on_serverlist_clicked(const QModelIndex &index);

  void on_favoritelist_clicked(const QModelIndex &index);

private:
  Ui::Lobby *ui;
  bool court_exists = false;

};

#endif // LOBBY_H
