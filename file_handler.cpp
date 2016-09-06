#include "file_handler.h"


QString getShowname(QString p_character)
{
  QFile char_ini(getBasePath() + "characters/" + p_character + "/char.ini");
  if (!char_ini.open(QIODevice::ReadOnly))
  {
    callError("failed to open " + getBasePath() + "characters/" + p_character + "/char.ini for reading. Setting showname to null.");
    return "null";
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
  }

  //if a showname couldnt be found, we simply return the characters technical name
  return p_character;
}
