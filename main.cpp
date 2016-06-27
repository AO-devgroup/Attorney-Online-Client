#include "main.h"
#include "lobby.h"
#include "courtroom.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Lobby w;
  //Courtroom c;
  w.show();
  //c.show();

  return a.exec();
}
