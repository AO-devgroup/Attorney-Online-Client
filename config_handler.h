#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QApplication>
#include <QStringList>

#include "error_handler.h"
#include "character_handler.h"

extern QStringList g_config_file;

QString getBasePath();

void LoadConfig();

QString getTheme();

QString getImagePath(QString image);

bool fileExists(QString path);

#endif // CONFIG_HANDLER_H
