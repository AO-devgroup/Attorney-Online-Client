#include "config_handler.h"

#include "courtroom.h"

QString getBasePath()
{
  return (QDir::currentPath() + "/base/");
}

QString getCharPath(QString character)
{
  return (getBasePath() + "characters/" + character + "/");
}

QString getCharGifPath(QString character, QString image)
{
  if (fileExists(getCharPath(character) + image, true))
    return (getCharPath(character) + image);
  else
    return get_image_path("placeholder.gif");
}

QString getCharEmotePath(QString character, QString emote)
{
  return (getCharPath(character) + emote);
}

QString getTheme()
{
  QFile config_file(getBasePath() + "config.ini");
  if (!config_file.open(QIODevice::ReadOnly))
  {
      callError("failed to open " + getBasePath() + "config.ini for reading. Setting theme to default.");
      return "default";
  }

  QTextStream in(&config_file);

  while(!in.atEnd())
  {
    QString line = in.readLine();

    if (line.startsWith("theme = "))
    {
      //removes "theme = " from the start of the line, then returns the rest
      return line.remove(0, 8);
    }
  }

  callError("Error: could not find theme in config.ini. Setting to default.");

  return "default";
}

QString Courtroom::get_background_path(QString p_bg_image)
{
  QString default_path = getBasePath() + "background/gs4/" + p_bg_image;
  QString path = background_path + p_bg_image;
  qDebug() << "background path = " << background_path;
  qDebug() << "path: " << path;

  if (fileExists(path, true))
  {
    return path;
  }
  else
  {
    return default_path;
  }
}

bool fileExists(QString path, bool quiet)
{
  QFileInfo check_file(path);

  if (check_file.exists() && check_file.isFile())
    return true;

  else if (quiet)
    return false;

  else
  {
    callError("Missing file: " + path);
    return false;
  }
}









