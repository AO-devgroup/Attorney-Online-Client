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
#include "error_handler.h"

QString getBasePath();

QString getCharPath(QString character);

QString getCharGifPath(QString character, QString gif);

QString getTheme();

bool fileExists(QString path, bool quiet = true);

#endif // CONFIG_HANDLER_H
