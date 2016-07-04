#include "config_handler.h"
#include "error_handler.h"

QString base_dir = (QDir::currentPath() + "/base/");

QString theme_path = (base_dir + "themes/" + getTheme() + "/");

QString characters_path = (base_dir + "characters/");

QString getTheme()
{
  QFile config_file(getConfigPath());
  if (!config_file.open(QIODevice::ReadOnly))
  {
      callError("Error: Failed to read " + base_dir + "config.ini");
  }
  QTextStream in(&config_file);

  while(!in.atEnd()) {
      QString line = in.readLine();
        if (line.startsWith("theme = "))
          //removes "theme = " from the start of the line, then returns the rest
          return line.remove(0, 8);
  }

  callError("Fatal error: could not find theme in config.ini");

}

QString getImagePath(QString image)
{
  return (theme_path + image);
}

QString getCharGifPath(QString image)
{
  return (characters_path + "Vinyl/" + image);
}

QString getConfigPath()
{
  return (base_dir + "config.ini");
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








