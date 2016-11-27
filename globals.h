#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>
#include <QTime>
#include <string>

#include "config_handler.h"

extern QString g_theme_path;

void set_theme_path();

QString get_image_path(QString p_image);

QString get_stylesheet_path(QString p_image);

bool cyclic_function();

QString incoming_network_formatter(QString input);

extern int pv;

extern unsigned int g_fantacrypt_key;

void set_fantacrypt_key(QString temp_decryptor);

QString fanta_encrypt(QString temp_input);

QString fanta_decrypt(QString temp_input, unsigned int key = 0);

void delay(int sec);

extern bool dank_memes;

extern const int RELEASE;

extern const int MAJOR_VERSION;

extern const int MINOR_VERSION;

#endif // GLOBALS_H
