#include "network_handler.h"

Networkhandler::Networkhandler(QObject *parent) : QObject(parent)
{
  ms_socket = new QTcpSocket(this);
  server_socket = new QTcpSocket(this);

  connect(ms_socket, &QTcpSocket::readyRead, this, &Networkhandler::handle_ms_packet);
  connect(server_socket, &QTcpSocket::readyRead, this, &Networkhandler::handle_server_packet);

  //T0D0: find a way to gracefully handle disconnects
  //connect(server_socket, SIGNAL(error(QAbstractSocket::disconnect())), this, SLOT(handle_server_disconnect()));

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

void Networkhandler::ms_send_message(QString p_packet)
{
  if (!master_connected)
    return;

  ms_socket->write(p_packet.toLocal8Bit());
}

void Networkhandler::ooc_send_message(QString p_packet)
{
  if (!server_connected)
    return;

  server_socket->write(p_packet.toLocal8Bit());
}

void Networkhandler::handle_chatmessage_request(chatmessage_type &p_chatmessage)
{
  if (!server_connected)
    return;

  //old format
  /*
  QString packet = "MS#" +
      p_chatmessage.message + "#" +
      p_chatmessage.character + "#" +
      p_chatmessage.side + "#" +
      p_chatmessage.sfx_name + "#" +
      p_chatmessage.pre_emote + "#" +
      p_chatmessage.emote + "#" +
      QString::number(p_chatmessage.emote_modifier) + "#" +
      QString::number(p_chatmessage.objection_modifier) + "#" +
      QString::number(p_chatmessage.realization) + "#" +
      QString::number(p_chatmessage.text_color) + "#" +
      QString::number(p_chatmessage.evidence) + "#%";
  */

  //MS#chat#<pre-emote>#<char>#<emote>#<message>#<side>#<sfx-name>#<emote_modifier>#<objection_modifier>#<realization>#<text_color>#<evidence>#<cid>#%
  QString packet = "MS#chat#" +
      p_chatmessage.pre_emote + "#" +
      p_chatmessage.character + "#" +
      p_chatmessage.emote + "#" +
      p_chatmessage.message + "#" +
      p_chatmessage.side + "#" +
      p_chatmessage.sfx_name + "#" +
      QString::number(p_chatmessage.emote_modifier) + "#" +
      QString::number(p_chatmessage.objection_modifier) + "#" +
      QString::number(p_chatmessage.realization) + "#" +
      QString::number(p_chatmessage.text_color) + "#" +
      QString::number(p_chatmessage.evidence) + "#" +
      //cid goes here
      "0#%";


  qDebug() << "sent packet: " << packet;

  server_socket->write(packet.toLocal8Bit());
}

void Networkhandler::handle_legacy_chatmessage_request(chatmessage_type &p_chatmessage)
{
  if (!server_connected)
    return;

  QString packet = "MS#chat#" +
      p_chatmessage.pre_emote + "#" +
      p_chatmessage.character + "#" +
      p_chatmessage.emote + "#" +
      p_chatmessage.message + "#";
      p_chatmessage.side + "#" +
      p_chatmessage.sfx_name + "#" +
      p_chatmessage.emote_modifier + "#0#0#" +
      p_chatmessage.objection_modifier + "#" +
      p_chatmessage.evidence + "#0#" +
      p_chatmessage.realization + "#" +
      p_chatmessage.text_color + "#%";



  qDebug() << "sent legacy packet: " << packet;

  server_socket->write(packet.toLocal8Bit());
}

void Networkhandler::handle_song_request(QString p_song_name)
{
  QString packet = "MC#" + p_song_name + "#%";

  server_socket->write(packet.toLocal8Bit());
}

void Networkhandler::handle_enter_server_request()
{
  if (!server_connected)
    return;

  //request characters, music and background
  server_socket->write("RC#%");
  server_socket->write("RM#%");
  server_socket->write("RB#%");
}

void Networkhandler::handle_character_request(QString p_character, QString p_password)
{
  QString packet = "UC#" + p_character + "#" + p_password + "#%";

  server_socket->write(packet.toLocal8Bit());
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
    QStringList packet_arguments = packet.split("#");

    QString header = packet_arguments.at(0);

    if (header == "CT")
    {
      if (packet_arguments.size() == 4)
        ms_message_received(packet_arguments.at(1) + ": " + packet_arguments.at(2));
      else if (packet_arguments.size() == 3)
        ms_message_received(packet_arguments.at(1));
      else
      {
        QString errorstring = "malformed masterserver packet. expected 4 or 3 packet arguments, got " + packet_arguments.size();
        callError(errorstring);
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
      int amount_of_servers = packet_arguments.size();

      qDebug() << "amount_of_servers: " << amount_of_servers;

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

  QString in_data;


  char buffer[2048] = {0};
  server_socket->read(buffer, server_socket->bytesAvailable());
  in_data = buffer;

  QStringList packet_list = in_data.split("%", QString::SplitBehavior(QString::SkipEmptyParts));

  for(QString packet : packet_list)
  {
    QStringList packet_contents = packet.split("#");

    QString header = packet_contents.at(0);

    //typically the first thing we get from the server when we connect
    if (header == "decryptor" || header == "HI")
    {
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
    else if (header == "SC")
    {

      QVector<char_type> f_char_list;

      for (int n_char = 0 ; n_char < packet_contents.size() - 2 ; ++n_char)
      {
        QStringList char_arguments =
          packet_contents.at(n_char + 1).split("&");

        if (char_arguments.size() != 4)
          callFatalError("malformed packet. expected char_arguments.size() to be 4, found" +
                         QString::number(char_arguments.size()));

        char_type f_char;

        f_char.name = char_arguments.at(0);
        f_char.description =  char_arguments.at(1);

        if (char_arguments.at(2) == "1")
          f_char.taken = true;

        else
          f_char.taken = false;

        if (char_arguments.at(3) == "1")
          f_char.passworded = true;

        else
          f_char.passworded = false;

        f_char_list.insert(n_char, f_char);
      }

      //we pass the vector to main_courtroom, because thats where its needed, implementation details on connecting
      //are found in main.cpp

      character_list_received(f_char_list);
    }

    //handles the music list packet
    else if (header == "SM")
    {
      QStringList f_music_list;

      for(int n_music = 0 ; n_music < packet_contents.size() - 2; ++n_music)
      {
        // + 1 to skip the header (which is in index 0) and shift everything one position
        f_music_list.insert(n_music, packet_contents.at(n_music + 1));
      }

      music_list_received(f_music_list);
    }

    else if (header == "SB")
    {
      QVector<area_type> f_area_list;

      //- 1 accounts for header
      for (int n_area = 0 ; n_area < packet_contents.size() - 2; ++n_area)
      {
        QStringList area_arguments =
          packet_contents.at(n_area + 1).split("&");

        if (area_arguments.size() != 3)
          callFatalError("malformed packet. expected area_arguments.size() to be 3, found" +
                         QString::number(area_arguments.size()));

        area_type f_area;

        f_area.name = area_arguments.at(0);
        f_area.background =  area_arguments.at(1);

        if (area_arguments.at(2) == "1")
          f_area.passworded = true;

        else
          f_area.passworded = false;

        f_area_list.insert(n_area, f_area);

        area_list_received(f_area_list);
      }
    }

    else if (header == "DONE")
    {
      done_signal();
    }

    else if (header == "OC")
    {
      if (packet_contents.size() != 4)
      {
        callError("(header = OC) Expected packet_contents.size() to be 4, but found " + packet_contents.size());
        return;
      }

      QString f_character = packet_contents.at(1);
      int f_mod = packet_contents.at(2).toInt();

      character_reply_received(f_character, f_mod);
    }

    else if (header == "MS")
    {
      chatmessage_type f_message;

      //old format
      /*
      if (packet_contents.size() == 12)
      {
        //message format:
        //0MS#1message#2character#3side#4sfx-name#5pre_emote#6emote#7emote_modifier#8objection_modifier#9realization#10text_color#11evidence#%

        f_message.message = packet_contents.at(1);
        f_message.character = packet_contents.at(2);
        f_message.side = packet_contents.at(3);
        f_message.sfx_name = packet_contents.at(4);
        f_message.pre_emote = packet_contents.at(5);
        f_message.emote = packet_contents.at(6);
        f_message.emote_modifier = packet_contents.at(7).toInt();
        f_message.objection_modifier = packet_contents.at(8).toInt();
        f_message.realization = packet_contents.at(9).toInt();
        f_message.text_color = packet_contents.at(10).toInt();
        f_message.evidence = packet_contents.at(11).toInt();
      }
      */

      if (packet_contents.size() == 15)
      {
        //format:
        //MS#chat#<pre-emote>#<char>#<emote>#<message>#<side>#<sfx-name>#<emote_modifier>#<objection_modifier>#<realization>#<text_color>#<evidence>#<cid>#%

        f_message.pre_emote = packet_contents.at(2);
        f_message.character = packet_contents.at(3);
        f_message.emote = packet_contents.at(4);
        f_message.message = packet_contents.at(5);
        f_message.side = packet_contents.at(6);
        f_message.sfx_name = packet_contents.at(7);
        f_message.emote_modifier = packet_contents.at(8).toInt();
        f_message.objection_modifier = packet_contents.at(9).toInt();
        f_message.evidence = packet_contents.at(10).toInt();
        f_message.realization = packet_contents.at(11).toInt();
        f_message.text_color = packet_contents.at(12).toInt();
      }

      else if (packet_contents.size() == 17)
      {
        //uh oh, we have a vanilla chatmessage on our hands
        //legacy message format:
        //MS0#1chat#2<pre emo>#3<char>#4<emo>#5<mes>#6<pos>#7<sfxname>#8<zoom>#9<cid>#10,1#11,0#12<evi>#13<cid>#14<bling>#15<color>#% main chat

        f_message.pre_emote = packet_contents.at(2);
        f_message.character = packet_contents.at(3);
        f_message.emote = packet_contents.at(4);
        f_message.message = packet_contents.at(5);
        f_message.side = packet_contents.at(6);
        f_message.sfx_name = packet_contents.at(7);
        f_message.emote_modifier = packet_contents.at(8).toInt();
        f_message.objection_modifier = packet_contents.at(11).toInt();
        f_message.evidence = packet_contents.at(12).toInt();
        f_message.realization = packet_contents.at(14).toInt();
        f_message.text_color = packet_contents.at(15).toInt();
      }

      else
      {
        callError("MALFORMED CHAT MESSAGE, expected size to be 15, found " + packet_contents.size());
        return;
      }

      chatmessage_received(f_message);
    }

    else if (header == "MC")
    {
      QString song_name = packet_contents.at(1);

      song_received(song_name);
    }

    else if (header == "CT")
    {
      QString name = packet_contents.at(1);
      QString message = packet_contents.at(2);

      ooc_message_received(name + ": " + message);
    }

    else if (header == "HP")
    {
      server_packet_received(packet);
    }


    qDebug() << "received packet: " << packet;
  }
}

void Networkhandler::send_packet(QString p_packet)
{
  if (!server_connected)
    return;

  server_socket->write(p_packet.toLocal8Bit());
}
