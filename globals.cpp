#include "globals.h"

QString g_theme_path = "FATAL: g_theme_path was not set";

const int RELEASE = 2;
const int MAJOR_VERSION = 0;
const int MINOR_VERSION = 8;

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

QString get_stylesheet_path(QString p_image)
{
  QString default_path = getBasePath() + "themes/default/" + p_image;
  QString image_path = g_theme_path + p_image;

  if (fileExists(image_path, true))
    return "border-image:url(\"" + image_path + "\")";
  else if (fileExists(default_path, true))
    return "border-image:url(\"" + default_path + "\")";
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

void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}
