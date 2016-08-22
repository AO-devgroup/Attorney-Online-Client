#include "network_handler.h"

Networkhandler::Networkhandler(QObject *parent) : QObject(parent)
{
  ms_socket = new QTcpSocket(this);
  server_socket = new QTcpSocket(this);

  connect(ms_socket, &QTcpSocket::readyRead, this, &Networkhandler::handle_ms_packet);
  connect(server_socket, &QTcpSocket::readyRead, this, &Networkhandler::handle_server_packet);

  connect(server_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handle_server_disconnect()));

  connect (ms_socket, SIGNAL(connected()), this, SLOT(ms_connection_established()));
  connect (ms_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ms_failed_to_connect()));

}

Networkhandler::~Networkhandler()
{
  delete ms_socket;
  delete server_socket;
}

void Networkhandler::connect_to_master()
{
  ms_socket->close();
  ms_socket->abort();

  ms_socket->connectToHost(ms_hostname, ms_port);
}

void Networkhandler::handle_server_disconnect()
{
  callError("Lost connection to server :v(");
  disconnect_from_server();
}

void Networkhandler::disconnect_from_server()
{
  server_connected = false;
  bool_character_list_received = false;
  bool_music_list_received = false;
  bool_character_list_received = false;

  server_socket->close();
  server_socket->abort();
}

void Networkhandler::connect_to_server(QString hostname, int port)
{
  disconnect_from_server();

  server_socket->connectToHost(hostname, port);
}

void Networkhandler::ms_failed_to_connect()
{
  callError("could not connect to masterserver :v(");
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

void Networkhandler::ms_send_message(QString packet)
{
  if (!master_connected)
    return;

  ms_socket->write(packet.toLocal8Bit());
}

void Networkhandler::handle_enter_server_request()
{
  //HACK, workaround for debugging on old server versions
  server_connected = true;

  if (!server_connected)
    return;

  initiate_loading_sequence();
}

void Networkhandler::initiate_loading_sequence()
{

  //server_socket->write("askchaa#%");

  //we cheat a bit because the network protocol isnt done yet
  //T0D0, fix when protocol is figured out
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

      m_server_list.clear();

      for (int n_server{1} ; n_server <= amount_of_servers ; ++n_server)
      {
        QString i_server = packet_arguments.at(n_server);
        server_type server;

        server.name = i_server.split("&").at(0);
        server.desc =  i_server.split("&").at(1);
        server.ip =  i_server.split("&").at(2);
        server.port =  i_server.split("&").at(3).toInt();

        m_server_list.insert(n_server - 1, server);
      }

    server_list_received(m_server_list);

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

    //typically the first thing we get from the server when we connect
    if (header == "decryptor" || header == "HI")
    {
      //QNetworkInterface f_interface;

      //we send HI# and our hardware address as our end of the handshake
      //QString packet = "HI#" + f_interface.hardwareAddress() + "#%";
      //callError(packet);
      //server_socket->write(packet.toLocal8Bit());

      //jk we send HI#<version>#% instead

      server_socket->write("HI#AO2#1.0.0#%");
    }

    //we usually receive this after sending HI#
    else if (header == "PN")
    {
      QString players_online = packet_contents.at(1);
      QString max_players = packet_contents.at(2);

      onlinestatus_changed(players_online, max_players);

      //server is now connected, but nothing is loaded yet
      server_connected = true;
    }

    //handles the character list packet
    else if (header == "CI")
    {

      QVector<char_type> f_char_list;

      for (int n_char = 0 ; n_char < packet_contents.size() ; ++n_char)
      {
        QStringList char_string_list =
          packet_contents.at(n_char + 1).split("&", QString::SplitBehavior(QString::SkipEmptyParts));

        if (char_string_list.size() != 3)
          callFatalError("malformed packet. expected char_string_list.size() to be 3, found" +
                         QString::number(char_string_list.size()));

        char_type f_char;

        f_char.name = char_string_list.at(0);
        f_char.description =  char_string_list.at(1);

        if (char_string_list.at(2) == "1")
          f_char.password = true;

        else
          f_char.password = false;

        f_char_list.insert(n_char, f_char);
      }

      //we pass the vector to main_courtroom, because thats where its needed, implementation details on connecting
      //are found in main.cpp

      character_list_received(f_char_list);

      bool_character_list_received = true;
    }

    //handles the music list packet
    else if (header == "EM")
    {
      QStringList f_music_list;

      for(int n_music = 0 ; n_music < packet_contents.size() ; ++n_music)
      {
        // + 1 to skip the header (which is in index 0) and shift everything one position
        f_music_list.insert(n_music, packet_contents.at(n_music + 1));
      }

      music_list_received(f_music_list);

      bool_music_list_received = true;
    }

    else if (header == "DONE")
    {
      //if (!bool_character_list_received)
      //  server_socket->write("ALL#%");

      done_loading();
    }
    qDebug() << packet;
  }
}
