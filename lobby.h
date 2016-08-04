#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>
#include <QFont>
#include <QString>
#include <QtNetwork>
#include <QDataStream>

#include "ui_lobby.h"
#include "courtroom.h"
#include "ui_courtroom.h"

#include "config_handler.h"
#include "error_handler.h"
#include "networking.h"

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
  int msPORT{27016};
  QTcpSocket *ms_socket;
  void refreshServerList();
  bool master_connected = false;
  //QDataStream in;

  ~Lobby();

public slots:

  //void lookedUp(QHostInfo);

  void handle_ms_packet();

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

private:
  Ui::Lobby *ui;
  bool court_exists = false;
};

#endif // LOBBY_H
