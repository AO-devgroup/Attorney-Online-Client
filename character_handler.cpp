#include "character_handler.h"

QStringList g_char_ini{"if this is visible anywhere, it means something broke"};

void LoadCharIni(QString character)
{
  QFile char_ini(getCharPath(character) + "char.ini");
  if (!char_ini.open(QIODevice::ReadOnly))
  {
      callError("failed to read " + getCharPath("Vinyl") + "char.ini");
      //QApplication::quit();
      //qApp->quit();
  }
  QTextStream in(&char_ini);

  int line_count{0};

  while(!in.atEnd())
  {
    g_char_ini.insert(line_count, in.readLine());
    ++line_count;
  }

}

int getEmoteNumber()
{

  QString line;

  for(int line_number{0} ; line_number < g_char_ini.size() ; ++line_number)
  {
    line = g_char_ini.at(line_number);

    if (line == "[Emotions]")
    {
      ++line_number;
      line = g_char_ini.at(line_number);

      if (!line.startsWith("number = "))
        callError("misconfigured char.ini. Expected \"number = \", found " + ::g_char_ini[line_number]);

      QString newline = line.remove(0, 9); //removes "number = " from the start of the line
      int output = newline.toInt();
      return output;
    }
  }

  callError("misconfigured char.ini. Could not find \"[Emotions]\".");

  return -1;
}


QString getCharPath(QString character)
{
  return (getBasePath() + "characters/" + character + "/");
}

QString getCharGifPath(QString character, QString image)
{
  return (getCharPath(character) + image);
}
