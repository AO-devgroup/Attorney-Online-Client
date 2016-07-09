#include "error_handler.h"

void callError(QString message)
{
  QMessageBox msgBox;
  msgBox.setText("Error: " + message);
  msgBox.setWindowTitle("Error");
  msgBox.exec();
}

void callFatalError(QString message)
{
  QMessageBox msgBox;
  msgBox.setText("FATAL ERROR: " + message + "\n\nquitting application");
  msgBox.setWindowTitle("FATAL ERROR");
  msgBox.exec();
  //appquit #T0D0
}


