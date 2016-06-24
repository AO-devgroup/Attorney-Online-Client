#include "config_handler.h"

QString base_dir = (QDir::currentPath() + "/base/");

QString user_theme_path = (base_dir + "themes/" + getUserTheme() + "/");

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
  return (user_theme_path + image);
}








