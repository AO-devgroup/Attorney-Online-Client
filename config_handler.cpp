#include "config_handler.h"


QString getBaseDir()
{
  return (QDir::currentPath() + "/base/");
}

QString getThemePath()
{
  return (getBaseDir() + "themes/" + getTheme() + "/");
}

QString getCharPath()
{
  return (getBaseDir() + "characters/");
}

QString getTheme()
{
  QFile config_file(getConfigPath());
  if (!config_file.open(QIODevice::ReadOnly))
  {
      callError("FATAL ERROR: Failed to read " + getBaseDir() + "config.ini");
      QApplication::quit();
  }
  QTextStream in(&config_file);

  while(!in.atEnd()) {
      QString line = in.readLine();
        if (line.startsWith("theme = "))
          //removes "theme = " from the start of the line, then returns the rest
          return line.remove(0, 8);
  }

  callError("Error: could not find theme in config.ini. Setting to default.");

  return "default";
}

QString getImagePath(QString image)
{
  return (getThemePath() + image);
}

QString getCharGifPath(QString image)
{
  return (getCharPath() + "Vinyl/" + image);
}

QString getConfigPath()
{
  return (getBaseDir() + "config.ini");
}

bool fileExists(QString path)
{
  QFileInfo check_file(path);

  if (check_file.exists() && check_file.isFile())
    return true;
  else
  {
    callError("Missing file: " + path);
    return false;
  }
}








