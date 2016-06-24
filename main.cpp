#include "main.h"
#include "lobby.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Lobby w;
  w.show();

  return a.exec();
}
