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

#include "error_handler.h"
#include "character_handler.h"
#include "datatypes.h"

extern QStringList g_config_file;

extern QVector<char_type> g_character_list;
extern QVector<evi_type> g_evidence_list;

QString getBasePath();

void LoadConfig();

QString getTheme();

QString getImagePath(QString image);

bool fileExists(QString path, bool quiet = false);

#endif // CONFIG_HANDLER_H
