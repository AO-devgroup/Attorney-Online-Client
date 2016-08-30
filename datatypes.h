#ifndef DATATYPES_H
#define DATATYPES_H

#include <QString>

struct server_type
{
  QString name;
  QString desc;
  QString ip;
  int port;
};

struct emote_type
{
  QString comment;
  QString preanim;
  QString anim;
  //this is always a number but since we never do arithmetic on it, we make it a string
  QString mod;
};

struct char_type
{
  QString name;
  QString description;
  bool taken;
  bool passworded;
};

struct evi_type
{
  QString name;
  QString description;
};

struct chatmessage_type
{
  QString message;
  QString character;
  QString emote;
  QString side;
  //a whole lot of other info #T0D0
};

#endif // DATATYPES_H
