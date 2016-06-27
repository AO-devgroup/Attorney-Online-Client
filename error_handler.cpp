#include "error_handler.h"

void callError(QString message)
{
  QMessageBox msgBox;
  msgBox.setText(message);
  msgBox.setWindowTitle("Error");
  msgBox.exec();
}
