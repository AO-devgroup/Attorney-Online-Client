#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDir>

extern QString base_dir; //should be available globally

QString getUserTheme();

QString getImagePath(QString image);

//deprecated

//QImage getUserBackground();
//QString getUserBackgroundPath();


#endif // CONFIG_HANDLER_H
