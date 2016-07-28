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

void Lobby::pingMaster()
{


  ms_socket->write("askforservers");
  //callError(ms_socket.bytesAvailable());
}

void Lobby::connectMaster()
{
  ms_socket->connectToHost("master.aceattorneyonline.com", msPORT);
}

void Lobby::readMaster()
{
  char buffer[1024] = {0};
  ms_socket->read(buffer, ms_socket->bytesAvailable());

  QString in_data = buffer;
  callError(in_data);

  //ms_socket->close();
}



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
