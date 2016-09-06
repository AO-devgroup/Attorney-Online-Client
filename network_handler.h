#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QNetworkInterface>

#include "datatypes.h"
#include "error_handler.h"

class Networkhandler : public QObject
{
  Q_OBJECT

public:

  explicit Networkhandler(QObject *parent = 0);
  ~Networkhandler();

  QTcpSocket *ms_socket;
  QTcpSocket *server_socket;

  bool master_connected = false;
  bool server_connected = false;

  QString ms_hostname = "dev.aceattorneyonline.com";
  int ms_port = 27016;

  QVector<server_type> m_server_list;

  void connect_to_master();
  void request_all_servers();
  void disconnect_from_server();

  bool packet_debugging = true;


signals:

  void ms_message_received(QString message);
  void ooc_message_received(QString p_message);

  void server_list_received(QVector<server_type> &f_server_list);

  void character_list_received(QVector<char_type> &f_char_list);

  void music_list_received(QStringList &f_music_list);

  void background_received(QString background);

  void onlinestatus_changed(QString players_online, QString max_players);

  void chatmessage_received(chatmessage_type &message);

  void song_received(QString song_name);

public slots:
  void connect_to_server(QString ip, int port);

  void handle_ms_packet();
  void handle_server_packet();

  void ms_connection_established();
  void ms_failed_to_connect();
  void ms_send_message(QString p_packet);
  void ooc_send_message(QString p_packet);

  void handle_all_servers_requested();

  void handle_enter_server_request();

  void handle_chatmessage_request(chatmessage_type &p_chatmessage);

  void handle_song_request(QString p_song_name);

private slots:
  void handle_server_disconnect();

};

#endif // NETWORKHANDLER_H
