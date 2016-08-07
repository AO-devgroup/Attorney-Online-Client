#include "main.h"

int main(int argc, char *argv[])
{

  QApplication a(argc, argv);
  Lobby w;
  //this prevents errors from ending the application
  a.setQuitOnLastWindowClosed(false);
  w.setTheme();
  w.connectMaster();
  w.show();

  return a.exec();
}
