#include "globals.h"

#include <cstddef>
#include <stdlib.h>
#include <sstream>
#include <iomanip>

#include <QDebug>
#include <QVector>

#include "hex_operations.h"

QString g_theme_path = "FATAL: g_theme_path was not set";

const int RELEASE = 2;
const int MAJOR_VERSION = 0;
const int MINOR_VERSION = 9;

//only this function should change g_theme_path
void set_theme_path()
{
  g_theme_path = getBasePath() + "themes/" + getTheme() + "/";
}

QString get_image_path(QString p_image)
{ 
  QString default_path = getBasePath() + "themes/default/" + p_image.toLower();
  QString image_path = g_theme_path + p_image.toLower();

  if (fileExists(image_path, true))
    return image_path;
  else if (fileExists(default_path, true))
    return default_path;
  else
    return "";

}

QString get_stylesheet_path(QString p_image)
{
  QString default_path = getBasePath() + "themes/default/" + p_image.toLower();
  QString image_path = g_theme_path + p_image.toLower();

  if (fileExists(image_path, true))
    return "border-image:url(\"" + image_path + "\")";
  else if (fileExists(default_path, true))
    return "border-image:url(\"" + default_path + "\")";
  else
    return "";
}

bool cyclic_function()
{
  static bool cycle = true;

  if (cycle)
  {
    cycle = false;
    return cycle;
  }

  else
  {
    cycle = true;
    return cycle;
  }
}

void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

//everything related to encryption under here
////////////////////////////////////////////////////////////////////////////////////////////////

//arbitrarily chosen
unsigned int g_fantacrypt_key = 5;

void set_fantacrypt_key(QString temp_decryptor)
{
  //first we need to decrypt the decryptor... I DID NOT DESIGN THIS OKAY
  //you may ask where 322 comes from... well, it's a random number chosen by fanatsors. magic.
  QString decryptor = fanta_decrypt(temp_decryptor, 322);

  g_fantacrypt_key = decryptor.toUInt();
}

QString fanta_encrypt(QString temp_input)
{
  //using standard stdlib types is actually easier here because of implicit char<->int conversion
  //which in turn makes encryption arithmetic easier

  unsigned int key = g_fantacrypt_key;
  unsigned int C1 = 53761;
  unsigned int C2 = 32618;

  QVector<uint_fast8_t> temp_result;
  std::string input = temp_input.toUtf8().constData();

  for (unsigned int pos = 0 ; pos < input.size() ; ++pos)
  {
    uint_fast8_t output = input.at(pos) ^ (key >> 8) % 256;
    temp_result.append(output);
    key = (temp_result.at(pos) + key) * C1 + C2;
  }

  std::string result = "";

  for (uint_fast8_t i_int : temp_result)
  {
    result += omni::int_to_hex(i_int);
  }

  QString final_result = QString::fromStdString(result);

  return final_result;
}

QString fanta_decrypt(QString temp_input, unsigned int key)
{
  //this means a key parameter was NOT passed and we use the global key
  //(if 0 is actually passed as a parameter, we have a problem... let's hope that doesn't happen)
  if (key == 0)
    key = g_fantacrypt_key;

  std::string input = temp_input.toUtf8().constData();

  QVector<unsigned int> unhexed_vector;

  for(int i=0; i< input.length(); i+=2)
  {
    std::string byte = input.substr(i,2);
    unsigned int hex_int = strtoul(byte.c_str(), nullptr, 16);
    unhexed_vector.append(hex_int);
  }

  unsigned int C1 = 53761;
  unsigned int C2 = 32618;

  std::string result = "";

  for (int pos = 0 ; pos < unhexed_vector.size() ; ++pos)
  {
    unsigned char output = unhexed_vector.at(pos) ^ (key >> 8) % 256;
    result += output;
    key = (unhexed_vector.at(pos) + key) * C1 + C2;
  }

  return QString::fromStdString(result);

}
