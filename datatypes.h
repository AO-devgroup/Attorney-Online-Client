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
  int mod;
};

struct char_type
{
  QString name;
  QString description;
  bool password;
};

struct evi_type
{
  QString name;
  QString description;
};

#endif // DATATYPES_H
