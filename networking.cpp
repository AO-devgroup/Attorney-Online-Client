#include "networking.h"
#include "courtroom.h"
#include "lobby.h"

//T0D0 fix this monstrosity

QStringList getServerList()
{
  //socket.whatever NETWORKING WHO KNOWS LOL
  QStringList serverlist =
  {"The Mank Server of Dank Memes", "ship", "ayy lmao", "hehehe", "hahhh", "HOH", "doritos",
   "mountain dew", "mank demes", "loomanardy", "shaoHIP", "im running out of dank memes",
   "LENGTHTEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEST", "hmm i wonder",
   "hehehe", "sho me your moves", "HOI", "hai", "eyyyyyyyyyyy"};

  return serverlist;

}

QStringList getCharSelectList()
{
  //server.connect i dunno man
  //to make later logic make sense we need to fill the 0 index with something(null)
  //currently there is a test set here
  QStringList charlist
  {
    "null",
    "Phoenix", "Oldbag", "Judge", "Miles", "Vinyl", "Butz", "Lotta", "Miles D", "Kristoph", "zettaslow"
  };

  return charlist;
}

void Courtroom::setTakenChars()
{
  //req from server teh taken char list ayy lmao
  QString string_from_server = "Charscheck#-1#0#0#0#0#0#0#0#0#-1#%";
  QStringList taken_chars_str;
  int taken_chars_size;

  string_from_server = string_from_server.toLower();
  taken_chars_str = string_from_server.split("#");

  //accounting for charscheck and %
  taken_chars_size = taken_chars_str.size() - 2;

  if (taken_chars_str.at(0) != "charscheck")
    callFatalError("malformed packet from server. (expected \"charscheck\", got " + taken_chars_str.at(0));

  if (taken_chars_str.at(taken_chars_size + 1) != "%")
    callFatalError("malformed packet from server. (expected \"%\", got " + taken_chars_str.at(taken_chars_size - 1));

  if (taken_chars_size != char_amount)
  {
    QString size = QString::number(taken_chars_size);
    QString amount = QString::number(char_amount);
    callFatalError("character amount did not match size of taken char list"
                   "char_amount: " + amount +
                   "taken_chars_size :" + size);
  }

  //we need to fill in the 0 index
  chars_taken.insert(0, -2);

  for(int n_char{1} ; n_char <= taken_chars_size ; ++n_char)
  {
    QString str_taken_or_not = taken_chars_str.at(n_char);
    int int_taken_or_not;

    int_taken_or_not = str_taken_or_not.toInt();

    chars_taken.insert(n_char, int_taken_or_not);
  }
}

//obsolete
/*
void Lobby::lookupMaster()
{
  QHostInfo::lookupHost("master.aceattorneyonline.com", this, SLOT(lookedUp(QHostInfo)));
}

void Lobby::lookedUp(QHostInfo host)
{
  if (host.error() != QHostInfo::NoError)
  {
    callError("master.aceattorneyonline.com could not resolve");
    return;
   }

   const auto addresses = host.addresses();
   //we just take the first address and be happy
   msIP = addresses.at(0);
}
*/

void Lobby::requestAllServers()
{
  if (!master_connected)
    return;

  ms_socket->write("ALL#%");
}

void Lobby::pingMaster()
{
  if (!master_connected)
    return;

  ms_socket->write("askforservers#%");
  //callError(ms_socket.bytesAvailable());
}

void Lobby::connectMaster()
{
  ms_socket->connectToHost(msHOST, msPORT);

  connect (ms_socket, SIGNAL(connected()), this, SLOT(ms_connection_established()));
  connect (ms_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ms_failed_to_connect()));
  //if ()
  //  master_connected = true;

  //else
  //  callError("Could not connect to master.");
}

void Lobby::ms_failed_to_connect()
{
  callError("Could not connect to masterserver :v(");
}

void Lobby::ms_connection_established()
{
  master_connected = true;
  requestAllServers();
}

void Lobby::handle_ms_packet()
{
  //ui->serverlist->addItem("hOI");

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



  //callError(in_data);
  //

  //ms_socket->close();
}

void Lobby::handle_server_packet()
{
  qDebug() << "Connected to " << int_selected_server;


}

void Lobby::on_chatmessage_returnPressed()
{
  if (!master_connected)
    return;

  QString name = ui->chatname->text();
  QString message = ui->chatmessage->text();
  QString packet = "CT#" + name + "#" + message + "#%";

  //no you cant send empty messages
  if ((name != "") && (message != ""))
  {
    ms_socket->write(packet.toLocal8Bit());
    ui->chatmessage->clear();
  }
}

void Lobby::server_connect(QString ip, int port)
{
  server_socket->close();

  server_socket->connectToHost(ip, port);
}

//replaced by requestAllServers()
/*
void Lobby::refreshServerList()
{

}
*/



/*
QVector<int> getTakenChars()
{
  //we ask the server for which chars are taken
  QVector<int> char_taken_list
  {
    0, -1, 0
  }

  return char_taken_list;
}
*/
