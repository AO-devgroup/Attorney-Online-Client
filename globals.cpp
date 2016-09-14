#include "globals.h"

QString g_theme_path = "FATAL: g_theme_path was not set";

//only this function should change g_theme_path
void set_theme_path()
{
  g_theme_path = getBasePath() + "themes/" + getTheme() + "/";
}

QString get_image_path(QString p_image)
{
  QString default_path = getBasePath() + "themes/default/" + p_image;
  QString image_path = g_theme_path + p_image;

  if (fileExists(image_path, true))
    return image_path;
  else if (fileExists(default_path))
    return default_path;
  else
    return "";

}
