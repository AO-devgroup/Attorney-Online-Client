#include "main.h"

int main(int argc, char *argv[])
{

  QApplication a(argc, argv);
  Lobby w;
  Courtroom s;
  Networkhandler n;
  s.hide();

  QObject::connect(&w, SIGNAL(done_loading()), &s, SLOT(initialize_courtroom()));

  //this prevents errors from ending the application
  //a.setQuitOnLastWindowClosed(false);
  w.setTheme();
  w.connectMaster();
  w.show();
  //w.requestAllServers();

  return a.exec();
}
