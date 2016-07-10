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
      //removes "number = " from the start of the line
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

    //in the unlikely event that we wont find [SoundN] and reach EOF
    if (line_number == (g_char_ini.size() - 1))
    {
      callError("could not find [Emotions] in char.ini");
      return -1;
    }

  }

  //we should not ever come here, but if the loop somehow finishes,
  //we return a -1 to signal the caller that something went wrong,

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

QString getEmoteIconPath(QString character, int emotenumber, bool onoroff)
{
  QString str_emotenumber = QString::number(emotenumber);

  QString smallb_on = getCharPath(character) + "emotions/button" + str_emotenumber + "_on.png";
  QString bigb_on = getCharPath(character) + "emotions/Button" + str_emotenumber + "_on.png";
  QString smallb_off = getCharPath(character) + "emotions/button" + str_emotenumber + "_off.png";
  QString bigb_off = getCharPath(character) + "emotions/Button" + str_emotenumber + "_off.png";

  if (onoroff)
  {
    if (fileExists(smallb_on, true))        //true makes the check quiet and does not throw an error..
      return smallb_on;                     //..if it fails

    else if (fileExists(bigb_on, true))
      return bigb_on;

    else
      return smallb_on;                     //at this point, we know the file doesnt exist, but..
  }                                         //..we return this and the caller handles the error

  else
  {
    if (fileExists(smallb_off, true))
      return smallb_off;

    else if (fileExists(bigb_off, true))
      return bigb_off;

    else
      return smallb_off;                    //same here
  }
}
