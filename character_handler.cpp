#include "character_handler.h"

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

int getEmoteNumber()
{
  bool found_emotions = false;
  QString line;

  for(int line_number{0} ; line_number < g_char_ini.size() ; ++line_number)
  {
    line = g_char_ini.at(line_number);

    //we are satisified if the line starts with target string
    //in case someone adds a space and wonders why things break
    if (line.startsWith("[Emotions]"))
      found_emotions = true;

    if (line.startsWith("number = ") && found_emotions)
    {
      //removes "number = " from the start of the string
      QString newline = line.remove(0, 9);

      //SANITY CHECK
      if (newline.toInt() < 1)
        callFatalError("number of emotes appear to be zero or negative");

      return newline.toInt();
    }

    if (line == "[SoundN]")
    {
      callError("[Emotions] in char.ini has been misplaced or does not exist. Make sure it is placed after [Time] and before [SoundN]");
      return -1;
    }

    //in the unlikely event that we dont find [SoundN] and reach EOF
    if (line_number == (g_char_ini.size() - 1))
    {
      callError("could not find [Emotions] in char.ini");
      return -1;
    }

  }

  //we should not ever come here, but if the loop somehow finishes
  //we return a -1 to signal the caller that something went wrong

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

QString getCharEmotePath(QString character, QString emote)
{
  return (getCharPath(character) + emote);
}
