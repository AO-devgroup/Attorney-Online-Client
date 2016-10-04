#include "globals.h"

QString g_theme_path = "FATAL: g_theme_path was not set";

const int RELEASE = 2;
const int MAJOR_VERSION = 0;
const int MINOR_VERSION = 6;

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
  else if (fileExists(default_path, true))
    return default_path;
  else
    return "";

}

QString get_background_path(QString p_background, QString p_bg_image)
{
  QString default_path = getBasePath() + "background/gs4/" + p_bg_image;
  QString path = getBasePath() + "background/" + p_background +  '/' + p_bg_image;

  if (fileExists(path, true))
    return path;
  else if (fileExists(default_path))
    return default_path;
  else
    return "";
}

bool cyclic_function()
{
  static bool cycle = true;

  if (cycle)
  {
    cycle = false;
    return cycle;
  }

  else
  {
    cycle = true;
    return cycle;
  }
}
