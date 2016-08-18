#include "networkhandler.h"

Networkhandler::Networkhandler(QObject *parent) : QObject(parent)
{

}

~Networkhandler()
{

}

void Networkhandler::requestAllServers()
{
  if (!master_connected)
    return;

  ms_socket->write("ALL#%");
}

void Networkhandler::handle_ms_packet()
{
  master_connected = true;

  char buffer[2048] = {0};
  ms_socket->read(buffer, ms_socket->bytesAvailable());

  QString in_data = buffer;

  QStringList packet_list = in_data.split("%");

  for (QString packet : packet_list)
  {
    QStringList packet_arguments = packet.split("#");

    QString header = packet_arguments[0];

    if (header == "CHECK")
      master_connected = true;

    else if (header == "CT")
    {
      if (packet_arguments.size() == 4)
        //ui->chatbox->addItem(packet_arguments[1] + ": " + packet_arguments[2]);
        ui->chatbox->appendPlainText(packet_arguments[1] + ": " + packet_arguments[2]);
      else if (packet_arguments.size() == 2)
        //ui->chatbox->addItem(packet_arguments[1]);
        ui->chatbox->appendPlainText(packet_arguments[1]);
      else
      {
        /*
        int size = packet_arguments.size();
        QString str_size = QString::number(size);
        ui->chatbox->addItem("Malformed CT packet. packet_arguments.size() = " + str_size + ". Expected 1 or 2");
        */
        ui->chatbox->appendPlainText(packet);
      }

    }
    else if (header == "servercheok")
    {
      ;
    }
    else if (header == "SN")
    {
      ui->chatbox->appendPlainText(packet);
      callError(":^)");
    }
    else if (header == "ALL")
    {
      int amount_of_servers = packet_arguments.size() - 2;

      qDebug() << "amount_of_servers: " << amount_of_servers;
      qDebug() << "packet: " << packet;

      QVector<server_type> server_list;

      for (int n_server{1} ; n_server <= amount_of_servers ; ++n_server)
      {
        QString i_server = packet_arguments.at(n_server);
        server_type server;

        server.name = i_server.split("&").at(0);
        server.desc =  i_server.split("&").at(1);
        server.ip =  i_server.split("&").at(2);
        server.port =  i_server.split("&").at(3).toInt();

        //QString server_name = packet_arguments.at(n_server).split("&").at(0);
        //QString server_desc = packet_arguments.at(n_server).split("&").at(1);

        server_list.insert(n_server - 1, server);

        //ui->serverlist->addItems(m_server_list);
      }

      m_server_list = server_list;

      ui->serverlist->clear();

      for (server_type server : m_server_list)
      {
        ui->serverlist->addItem(server.name);
      }
      //ui->serverlist->addItems(server_list);
    }
    else
    {
      ;
    }
  }


void Networkhandler::handle_server_packet()
{
  server_connected = true;

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

      ui->onlinestatus->setText("Online: " + players_online + "/" + max_players);
    }

    else if (header == "SI")
    {
      int int_charsize = packet_contents.at(1).toInt();
      int int_evisize = packet_contents.at(2).toInt();
      int int_musicsize = packet_contents.at(3).toInt();

      charlist_size = int_charsize;
      evidence_size = int_evisize;
      musiclist_size = int_musicsize;
      array_sizes_set = true;
    }

    else if (header == "CI")
    {
      //all instances of this are just placeholders for charlist_size until server protocol is fixed
      int temp_charlist_size = 9;

      if (!array_sizes_set)
        continue;

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

    else if (header == "decryptor")
    {
      establish_connection();
    }

    else if (header == "DONE")
    {
      done_loading();
    }
    qDebug() << packet;
  }



}
