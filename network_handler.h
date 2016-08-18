#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QString>

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

  QString ms_hostname = "master.aceattorneyonline.com";
  int ms_port = 27016;

  QVector<server_type> ms_server_list;

  void connect_to_master();
  void request_all_servers();
  void initiate_handshake();
  void initiate_loading_sequence();


signals:

  void ms_message_received(QString message);

  void server_list_received(QVector<server_type> &server_list);

  void onlinestatus_changed(QString players_online, QString max_players);

  void done_loading();

public slots:
  void connect_to_server(QString ip, int port);

  void handle_ms_packet();
  void handle_server_packet();

  void ms_connection_established();
  void ms_failed_to_connect();
  void ms_send_message(QString packet);

  void handle_all_servers_requested();

  void handle_enter_server_request();

private slots:
  void handle_server_disconnect();

};

#endif // NETWORKHANDLER_H
