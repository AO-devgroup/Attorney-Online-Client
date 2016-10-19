#include "file_handler.h"

#include <QDebug>


QString getShowname(QString p_character)
{
  QFile char_ini(getBasePath() + "characters/" + p_character + "/char.ini");
  if (!char_ini.open(QIODevice::ReadOnly))
  {
   return p_character;
  }

  QTextStream in(&char_ini);

  while(!in.atEnd())
  {
    QString line = in.readLine();
    if (line.startsWith("showname = "))
    {
      //removes showname = and returns
      return line.remove(0, 11);
    }

    else if (line.startsWith("showname ="))
    {
      return line.remove(0, 10);
    }

    else if (line.startsWith("showname= "))
    {
      return line.remove(0, 10);
    }

    else if (line.startsWith("showname="))
    {
      return line.remove(0, 9);
    }
  }

  //if a showname couldnt be found, we simply return the characters technical name
  return p_character;
}

QString getGender(QString p_character)
{
  QFile char_ini(getBasePath() + "characters/" + p_character + "/char.ini");
  if (!char_ini.open(QIODevice::ReadOnly))
  {
    return "male";
  }

  QTextStream in(&char_ini);

  while(!in.atEnd())
  {
    QString line = in.readLine().toLower().trimmed();

    QString searchline1 = "gender =";
    QString searchline2 = "gender=";

    if (line.startsWith(searchline1))
    {
      //removes gender = and returns
      return line.remove(0, searchline1.length()).trimmed();
    }

    else if (line.startsWith(searchline2))
    {
      return line.remove(0, searchline2.length()).trimmed();
    }
  }

  //if a gender couldnt be found, we assume male and be done with it
  return "male";
}

QString getChat(QString p_character)
{
  QFile char_ini(getBasePath() + "characters/" + p_character + "/char.ini");
  if (!char_ini.open(QIODevice::ReadOnly))
  {
    char_ini.close();
    return "default";
  }

  QTextStream in(&char_ini);

  while(!in.atEnd())
  {
    QString line = in.readLine().toLower().trimmed();

    QString searchline1 = "chat =";
    QString searchline2 = "chat=";

    if (line.startsWith(searchline1))
    {
      char_ini.close();
      return line.remove(0, searchline1.length()).trimmed();
    }

    else if (line.startsWith(searchline2))
    {
      char_ini.close();
      return line.remove(0, searchline2.length()).trimmed();
    }
  }

  char_ini.close();
  return "default";
}

int get_preanim_duration(QString p_character, QString p_emote)
{
  QFile char_ini(getBasePath() + "characters/" + p_character.toLower() + "/char.ini");
  if (!char_ini.open(QIODevice::ReadOnly))
  {
    char_ini.close();
    return 0;
  }

  QTextStream in(&char_ini);

  //again, we need two search line because of i n c o n s i s t e n c i e s
  QString search_line1 = p_emote + " =";
  QString search_line2 = p_emote + "=";

  while(!in.atEnd())
  {
    QString line = in.readLine().toLower().trimmed();

    if (line.startsWith(search_line1))
    {
      char_ini.close();
      return line.remove(0, search_line1.length()).trimmed().toInt();
    }

    if (line.startsWith(search_line2))
    {
      char_ini.close();
      return line.remove(0, search_line2.length()).trimmed().toInt();
    }
  }

  char_ini.close();
  return 0;
}


