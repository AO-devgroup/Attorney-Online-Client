#include "character_handler.h"

std::vector<QString> g_char_ini{"IOh"};

void LoadCharIni()
{
  QFile char_ini(getCharPath("Vinyl") + "char.ini");
  if (!char_ini.open(QIODevice::ReadOnly))
  {
      callError("FATAL ERROR: Failed to read " + getCharPath("Vinyl") + "char.ini");
      //QApplication::quit();
      //qApp->quit();
  }
  QTextStream in(&char_ini);

  int line_count{0};

  while(!in.atEnd())
  {
    g_char_ini[line_count] = in.readLine();
    ++line_count;
  }
}

int getEmoteNumber()
{

  for(QString line : ::g_config_file)
  {
    if (line.startsWith("number = "))
    {
      QString newline = line.remove(0, 9); //removes "number = " from the start of the line
      return newline.toInt();
    }
  }

  callError("emote number not found. Setting to 10.");

  return 10;
}


QString getCharPath(QString character)
{
  return (getBasePath() + "characters/" + character + "/");
}

QString getCharGifPath(QString character, QString image)
{
  return (getCharPath(character) + image);
}
