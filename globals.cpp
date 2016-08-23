#include "globals.h"

QString g_theme_path = "FATAL: g_theme_path was not set";

//only this function should change g_theme_path
void set_theme_path()
{
  g_theme_path = getBasePath() + "themes/" + getTheme() + "/";
}
