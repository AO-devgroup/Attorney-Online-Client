#include "config_handler.h"

QStringList g_config_file{"if this is visible anywhere, it means something broke"};

QString getBasePath()
{
  return (QDir::currentPath() + "/base/");
}

void LoadConfig()
{
  QFile config_file(getBasePath() + "config.ini");
  if (!config_file.open(QIODevice::ReadOnly))
  {
      callError("FATAL ERROR: Failed to read " + getBasePath() + "config.ini");
      //QApplication::quit();
      qApp->quit();
  }
  QTextStream in(&config_file);

  int line_count{0};

  while(!in.atEnd())
  {
    g_config_file.insert(line_count, in.readLine());
    ++line_count;
  }
}

QString getTheme()
{
  //int config_size = ::g_config_file.size();

  //QTextStream in(getConfigFile());

  //StringList config_file = ::g_config_file;

  for(QString line : ::g_config_file)
  {
    if (line.startsWith("theme = "))
      //removes "theme = " from the start of the line, then returns the rest
      return line.remove(0, 8);
  }

  callError("Error: could not find theme in config.ini. Setting to default.");

  return "default";
}

QString getImagePath(QString image)
{
  return (getBasePath() + "themes/" + getTheme() + "/" + image);
}

bool fileExists(QString path)
{
  QFileInfo check_file(path);

  if (check_file.exists() && check_file.isFile())
    return true;
  else
  {
    callError("Missing file: " + path);
    return false;
  }
}








