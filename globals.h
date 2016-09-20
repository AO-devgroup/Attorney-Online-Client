#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>

#include "config_handler.h"

extern QString g_theme_path;

void set_theme_path();

QString get_image_path(QString p_image);

QString get_background_path(QString p_background, QString p_background_image);

#endif // GLOBALS_H
