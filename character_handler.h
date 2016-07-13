#ifndef CHARACTER_HANDLER_H
#define CHARACTER_HANDLER_H

#include <QFile>
#include <QTextStream>

#include "config_handler.h"
#include "error_handler.h"

extern QStringList g_char_ini;

void LoadCharIni(QString character);

QString getCharPath(QString character);

QString getCharGifPath(QString character, QString gif);


#endif // CHARACTER_HANDLER_H
