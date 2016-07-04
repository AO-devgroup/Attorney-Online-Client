#include "config_handler.h"
#include "error_handler.h"

QString base_dir = (QDir::currentPath() + "/base/");

QString theme_path = (base_dir + "themes/" + getTheme() + "/");

QString characters_path = (base_dir + "characters/");

QString getTheme()
{
  QFile config_file(base_dir + "config.ini");
  if (!config_file.open(QIODevice::ReadOnly))
  {
      callError("Failed to read " + base_dir + "config.ini");
  }
  QTextStream in(&config_file);
  QString config_string = in.readLine();
  config_file.close();
  return config_string;
}

QString getImagePath(QString image)
{
  return (theme_path + image);
}

QString getCharGifPath(QString image)
{
  return (characters_path + "Vinyl/" + image);
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








