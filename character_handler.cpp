#include "character_handler.h"

//obsolete, needs to be replaced #T0D0
QStringList g_char_ini{"if this is visible anywhere, it means that char.ini failed to load into memory"};

void LoadCharIni(QString character)
{
  QFile char_ini(getCharPath(character) + "char.ini");
  if (!char_ini.open(QIODevice::ReadOnly))
  {
      callFatalError("failed to read " + getCharPath(character) + "char.ini");
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

QString getCharPath(QString character)
{
  return (getBasePath() + "characters/" + character + "/");
}

QString getCharGifPath(QString character, QString image)
{
  return (getCharPath(character) + image);
}

QString getCharEmotePath(QString character, QString emote)
{
  return (getCharPath(character) + emote);
}
