#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QApplication>
#include <QStringList>
#include <QVector>

#include "datatypes.h"

#include "lobby.h"
#include "error_handler.h"


//obsolete
//extern QStringList g_config_file;



QString getBasePath();

//void LoadConfig();

QString getTheme();

//QString getImagePath(QString image);

bool fileExists(QString path, bool quiet = false);

#endif // CONFIG_HANDLER_H
