#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include "error_handler.h"

QString getTheme();

QString getImagePath(QString image);

QString getCharGifPath(QString image);

bool fileExists(QString path);

//deprecated

//QImage getUserBackground();
//QString getUserBackgroundPath();


#endif // CONFIG_HANDLER_H
