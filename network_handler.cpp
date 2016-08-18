#include "network_handler.h"

Networkhandler::Networkhandler(QObject *parent) : QObject(parent)
{
  ms_socket = new QTcpSocket(this);
  server_socket = new QTcpSocket(this);

  connect(ms_socket, &QTcpSocket::readyRead, this, &Networkhandler::handle_ms_packet);
  connect(server_socket, &QTcpSocket::readyRead, this, &Networkhandler::handle_server_packet);

  connect(server_socket, SIGNAL(disconnected()), this, SLOT(handle_server_disconnect()));

  connect (ms_socket, SIGNAL(connected()), this, SLOT(ms_connection_established()));
  connect (ms_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ms_failed_to_connect()));

}

Networkhandler::~Networkhandler()
{

}

void Networkhandler::connect_to_master()
{
  ms_socket->close();
  ms_socket->abort();

  ms_socket->connectToHost(ms_hostname, ms_port);
}

void Networkhandler::connect_to_server(QString hostname, int port)
{
  server_connected = false;
  server_socket->close();
  server_socket->abort();

  server_socket->connectToHost(hostname, port);
}

void Networkhandler::ms_failed_to_connect()
{
  callError("could not connect to masterserver :v(");
}

void Networkhandler::handle_server_disconnect()
{
  server_connected = false;
}

void Networkhandler::ms_connection_established()
{

}

void Networkhandler::handle_all_servers_requested()
{
  request_all_servers();
}

void Networkhandler::request_all_servers()
{
  if (!master_connected)
    return;

  ms_socket->write("ALL#%");
}

void Networkhandler::initiate_handshake()
{
  server_socket->write("HI#dontworryitsmeomnitroidimjusttestingforao2#%");
}

void Networkhandler::ms_send_message(QString packet)
{
  if (!master_connected)
    return;

  ms_socket->write(packet.toLocal8Bit());
}

void Networkhandler::handle_enter_server_request()
{
  if (!server_connected)
    return;

  initiate_loading_sequence();
}

void Networkhandler::initiate_loading_sequence()
{

  server_socket->write("askchaa#%");

  //we cheat a bit because the network protocol isnt done yet
  done_loading();
}

void Networkhandler::handle_ms_packet()
{
  master_connected = true;

  char buffer[2048] = {0};
  ms_socket->read(buffer, ms_socket->bytesAvailable());

  QString in_data = buffer;

  QStringList packet_list = in_data.split("%", QString::SplitBehavior(QString::SkipEmptyParts));

  for (QString packet : packet_list)
  {
    QStringList packet_arguments = packet.split("#", QString::SplitBehavior(QString::SkipEmptyParts));

    QString header = packet_arguments[0];

    if (header == "CT")
    {
      if (packet_arguments.size() == 3)
        ms_message_received(packet_arguments[1] + ": " + packet_arguments[2]);
      else if (packet_arguments.size() == 1)
        ms_message_received(packet_arguments[1]);
      else
      {
        ;
      }
    }

    else if (header == "servercheok")
    {
      request_all_servers();
    }

    else if (header == "CHECK")
      continue;

    else if (header == "ALL")
    {
      int amount_of_servers = packet_arguments.size() - 2;

      qDebug() << "amount_of_servers: " << amount_of_servers;

      QVector<server_type> server_list;

      ms_server_list.clear();

      for (int n_server{1} ; n_server <= amount_of_servers ; ++n_server)
      {
        QString i_server = packet_arguments.at(n_server);
        server_type server;

        server.name = i_server.split("&").at(0);
        server.desc =  i_server.split("&").at(1);
        server.ip =  i_server.split("&").at(2);
        server.port =  i_server.split("&").at(3).toInt();

        ms_server_list.insert(n_server - 1, server);
      }

    server_list_received(ms_server_list);

    }

    qDebug() << packet;
  }

}


void Networkhandler::handle_server_packet()
{
  char buffer[2048] = {0};
  server_socket->read(buffer, server_socket->bytesAvailable());

  QString in_data = buffer;

  QStringList packet_list = in_data.split("%", QString::SplitBehavior(QString::SkipEmptyParts));

  for(QString packet : packet_list)
  {
    QStringList packet_contents = packet.split("#", QString::SplitBehavior(QString::SkipEmptyParts));

    QString header = packet_contents.at(0);

    if (header == "PN")
    {
      QString players_online = packet_contents.at(1);
      QString max_players = packet_contents.at(2);

      onlinestatus_changed(players_online, max_players);
    }

    //need updated network protocol before we can make this work
    /*
    else if (header == "CI")
    {
      //all instances of this are just placeholders for charlist_size until server protocol is fixed
      //
      int temp_charlist_size = 9;

      //if (!array_sizes_set)
      //  continue;

      if (!(packet_contents.size() == temp_charlist_size + 2))
      {
        QString err_str = QString::number(temp_charlist_size + 2);
        QString err_str2 = QString::number(packet_contents.size());

        callError("MALFORMED PACKET. EXPECTED " + err_str2 + ", got " + err_str);
        continue;
      }

      for(int n_char = 0 ; n_char <= temp_charlist_size ; ++n_char)
      {

        //char_vector.clear();

        //the 2 here accounts for CI and <cid>
        char_vector.insert(n_char, packet_contents.at(n_char + 2));
      }
    }
    */

    else if (header == "ID")
    {
      //if we receive ID# with server version we consider the handshake successful and the connection established
      server_connected = true;
    }


    else if (header == "decryptor")
    {
      initiate_handshake();
    }

    else if (header == "DONE")
    {
      //make checks to make sure we got everything somewhere in the code, T0D0
      done_loading();
    }
    qDebug() << packet;
  }
}
