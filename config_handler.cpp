#include "config_handler.h"

QString base_dir = (QDir::currentPath() + "/base/");

QString theme_path = (base_dir + "themes/" + getUserTheme() + "/");

QString characters_path = (base_dir + "characters/");

QString getUserTheme()
{
  QFile config_file(base_dir + "config.ini");
  if (!config_file.open(QIODevice::ReadOnly))
  {
      //callFileReadError #T0D0
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

bool fileExists(QString path) { //check file existence and makes sure its not a directory
    QFileInfo check_file(path);
    return (check_file.exists() && check_file.isFile());
}








