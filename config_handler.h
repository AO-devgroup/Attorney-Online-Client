#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDir>
#include <QFileInfo>

QString getUserTheme();

QString getImagePath(QString image);

bool fileExists(QString path);

//deprecated

//QImage getUserBackground();
//QString getUserBackgroundPath();


#endif // CONFIG_HANDLER_H
