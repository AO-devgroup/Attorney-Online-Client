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
#include "datatypes.h"

namespace Ui {
class Lobby;
}

class Lobby : public QMainWindow
{
  Q_OBJECT

public:
  explicit Lobby(QWidget *parent = 0);

  void setTheme();
  void LoadFavorites();

  QVector<server_type> m_server_list;

  int int_selected_server = -1;
  bool public_servers_selected = true;

  QVector<server_type> favoriteservers;
  QFile favoritefile;

  QVector<QString> char_vector;
  QVector<QString> evidence_vector;
  QVector<QString> music_vector;

  ~Lobby();

public slots:

  void handle_ms_message(QString message);

  void update_server_list(QVector<server_type> &server_list);

  void update_onlinestatus(QString players_online, QString max_players);

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

signals:
  void all_servers_requested();
  void server_connection_requested(QString ip, int port);
  void ms_message_requested(QString packet);
  void enter_server_requested();
  //void server_disconnect_requested();

};

#endif // LOBBY_H
