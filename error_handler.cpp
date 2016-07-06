#include "error_handler.h"

void callError(QString message)
{
  QMessageBox msgBox;
  msgBox.setText("Error: " + message);
  msgBox.setWindowTitle("Error");
  msgBox.exec();
}


