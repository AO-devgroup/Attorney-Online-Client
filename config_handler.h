#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QApplication>
#include "error_handler.h"

QString getBasePath();

QString getThemePath();

QString getCharPath();

QString getTheme();

QString getImagePath(QString image);

QString getCharGifPath(QString image);

QString getConfigPath();

bool fileExists(QString path);

//deprecated

//QImage getUserBackground();
//QString getUserBackgroundPath();


#endif // CONFIG_HANDLER_H
