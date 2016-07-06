#ifndef CHARACTER_HANDLER_H
#define CHARACTER_HANDLER_H

#include <QFile>
#include <QTextStream>

#include "config_handler.h"
#include "error_handler.h"

extern std::vector<QString> g_config_file;

void LoadCharIni();

int getEmoteNumber();

QString getCharPath(QString character);

QString getCharGifPath(QString character, QString gif);


#endif // CHARACTER_HANDLER_H
