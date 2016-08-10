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

#endif // DATATYPES_H
