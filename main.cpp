#include "main.h"

int main(int argc, char *argv[])
{

  QApplication a(argc, argv);
  Lobby w;
  w.setTheme();
  w.show();

  return a.exec();
}
