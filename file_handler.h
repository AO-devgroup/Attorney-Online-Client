#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <QString>
#include <QFile>
#include "config_handler.h"

QString getShowname(QString p_character);

QString getGender(QString p_character);

QString getChat(QString p_character);

int get_preanim_duration(QString p_character, QString p_emote);

#endif // FILE_HANDLER_H
