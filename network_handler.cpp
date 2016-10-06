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
  //callError("Lost connection to server :v(");
  disconnect_signal();
  //disconnect_from_server();
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

  ms_socket->write(p_packet.toUtf8());
  qDebug() << "sent message: " << p_packet.toUtf8();
}

void Networkhandler::ooc_send_message(QString p_packet)
{
  if (!server_connected)
    return;

  server_socket->write(p_packet.toUtf8());
}

void Networkhandler::handle_chatmessage_request(chatmessage_type &p_chatmessage)
{
  if (!server_connected)
    return;

  QString packet = "MS#chat#" +
      p_chatmessage.pre_emote + "#" +
      p_chatmessage.character + "#" +
      p_chatmessage.emote + "#" +
      p_chatmessage.message + "#" +
      p_chatmessage.side + "#" +
      p_chatmessage.sfx_name + "#" +
      QString::number(p_chatmessage.emote_modifier) + "#" +
      QString::number(p_chatmessage.cid) + "#" +
      QString::number(p_chatmessage.sfx_delay) + "#" +
      QString::number(p_chatmessage.objection_modifier) + "#" +
      QString::number(p_chatmessage.evidence) + "#" +
      QString::number(p_chatmessage.flip) + "#" +
      QString::number(p_chatmessage.realization) + "#" +
      QString::number(p_chatmessage.text_color) + "#%";

  qDebug() << "sent packet: " << packet;

  server_socket->write(packet.toUtf8());
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
  server_socket->write("RA#%");
  //this usually gets spit out as one packet because of nagle's algorithm
}

void Networkhandler::handle_character_request(int p_character, QString p_password)
{
  QString packet = "UC#" + QString::number(p_character) + "#" + p_password + "#%";

  server_socket->write(packet.toLocal8Bit());
}

void Networkhandler::handle_ms_packet()
{
  master_connected = true;

  char buffer[16384] = {0};
  ms_socket->read(buffer, ms_socket->bytesAvailable());

  QString in_data = buffer;

  if (!in_data.endsWith("%"))
  {
    qDebug() << "partial_packet set to true!";
    partial_packet = true;
    temp_packet += in_data;
    qDebug() << "current temp_packet: " << temp_packet;
    return;
  }

  else
  {
    if (partial_packet)
    {
      qDebug() << "found partial_packet to be true!";
      in_data = temp_packet + in_data;
      qDebug() << "FINAL in_data: " << in_data;
      temp_packet = "";
      qDebug() << "partial_packet set to false!";
      partial_packet = false;
    }
  }

  QStringList packet_list; //= in_data.split("%", QString::SplitBehavior(QString::SkipEmptyParts));

  //HACK to compensate for a masterserver bug
  packet_list.append(in_data);

  for (QString packet : packet_list)
  {
    QStringList packet_arguments = packet.split("#");

    QString header = packet_arguments.at(0);

    if (header == "CT")
    {
      if (packet_arguments.size() == 4)
      {
        QString msg = packet_arguments.at(1) + ": " + packet_arguments.at(2);
        ms_message_received(msg.replace("<percent>", "%").replace("<num>", "#"));
      }
      else if (packet_arguments.size() == 3)
      {
        QString msg = packet_arguments.at(1);
        ms_message_received(msg.replace("<percent>", "%").replace("<num>", "#"));
      }
      else
      {
        QString errorstring = "malformed masterserver packet. expected 4 or 3 packet arguments, got " + packet_arguments.size();
        callError(errorstring);
      }
    }

    else if (header == "servercheok")
    {
      //qDebug() << packet;

      int f_release = packet_arguments.at(1).split(".").at(0).toInt();
      int f_major = packet_arguments.at(1).split(".").at(1).toInt();
      //int f_minor = packet_arguments.at(1).split(".").at(2).toInt();

      if (MAJOR_VERSION < f_major)
      {
        if (RELEASE <= f_release)
        {
          QString msg = "Client outdated! Your version: " +
              QString::number(RELEASE) + "." +
              QString::number(MAJOR_VERSION) + "." +
              QString::number(MINOR_VERSION) +
              "\nVisit aceattorneyonline.com to update!";
          callFatalError(msg, false);
          request_quit();
          return;
        }
      }

      request_all_servers();
    }

    else if (header == "ALL")
    { 
      qDebug() << "ALL packet: " << packet;

      for (QString server : packet_arguments)
      {
        //qDebug() << "server: " << server;
      }

      int amount_of_servers = packet_arguments.size() - 2;

      qDebug() << "amount_of_servers: " << amount_of_servers;

      m_server_list.clear();

      for (int n_server{1} ; n_server <= amount_of_servers ; ++n_server)
      {
        QString i_server = packet_arguments.at(n_server);
        server_type server;

        QString f_name = i_server.split("&").at(0);
        QString f_desc = i_server.split("&").at(1);
        QString f_ip = i_server.split("&").at(2);
        QString f_port = i_server.split("&").at(3);

        server.name = f_name.replace("<percent>", "%").replace("<num>", "#");
        server.desc =  f_desc.replace("<percent>", "%").replace("<num>", "#");
        server.ip = f_ip.replace("<percent>", "%").replace("<num>", "#");
        server.port =  f_port.toInt();

        m_server_list.insert(n_server - 1, server);
      }

    server_list_received(m_server_list);

    }

    //qDebug() << packet;
  }

}

void Networkhandler::handle_server_packet()
{
  QString in_data;

  //we go nuts now
  char buffer[500000] = {0};
  server_socket->read(buffer, server_socket->bytesAvailable());
  in_data = buffer;

  if (!in_data.endsWith("%"))
  {
    partial_packet = true;
    temp_packet += in_data;
    return;
  }

  else
  {
    if (partial_packet)
    {
      in_data = temp_packet + in_data;
      temp_packet = "";
      partial_packet = false;
    }
  }

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

    else if (header == "TC")
    {
      QVector<int> f_taken_list;

      for (int n_char = 0 ; n_char < packet_contents.size() - 2 ; ++n_char)
      {
        int f_taken = packet_contents.at(n_char + 1).toInt();

        f_taken_list.insert(n_char, f_taken);
      }

      taken_list_received(f_taken_list);

      qDebug() << packet;
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

    else if (header == "SA")
    {
      QVector<area_type> f_area_list;

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
      }

      area_list_received(f_area_list);
    }

    else if (header == "TA")
    {
      QVector<int> f_area_taken_list;

      for (int n_area = 0; n_area < packet_contents.size() - 2 ; ++n_area)
      {
        f_area_taken_list.insert(n_area, packet_contents.at(n_area + 1).toInt());
      }

      area_taken_list_received(f_area_taken_list);

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

      int f_character = packet_contents.at(1).toInt();
      int f_mod = packet_contents.at(2).toInt();

      character_reply_received(f_character, f_mod);
    }

    else if (header == "MS")
    {
      //chatmessage_type f_message;

      if (packet_contents.size() == 17)
      {
        /*
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
        */

        server_packet_received(packet);
      }

      /*
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
      */

      else
      {
        //T0D0 find a non-intrusive way of reporting that something went wrong
        //callError("MALFORMED CHAT MESSAGE, expected size to be 15, found " + packet_contents.size());
        qDebug() << packet;
        return;
      }

      //chatmessage_received(f_message);
    }

    else if (header == "MC")
    {
      server_packet_received(packet);

      //QString song_name = packet_contents.at(1);

      //song_received(song_name);
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

    else if (header == "RT")
    {
      server_packet_received(packet);
    }

    else if (header == "OA")    
    {
      server_packet_received(packet);
    }

    else if (header == "PING")
    {
      server_socket->write("PONG#%");
    }

    else if (header == "BD")
    {
      callError("You are banned on this server.");
    }

    else
      server_packet_received(packet);


    qDebug() << "received packet: " << packet;
  }
}

void Networkhandler::send_packet(QString p_packet)
{
  if (!server_connected)
    return;

  server_socket->write(p_packet.toLocal8Bit());
  qDebug() << "Sent packet: " << p_packet;
}

void Networkhandler::close_socket()
{
  server_socket->close();
}
