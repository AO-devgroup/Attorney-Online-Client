#include "error_handler.h"

void callError(QString message, bool error_text)
{
  QMessageBox *msgBox = new QMessageBox;


  if (error_text)
  {
    msgBox->setText("Error: " + message);
    msgBox->setWindowTitle("Error");
  }

  else
  {
    msgBox->setText(message);
    msgBox->setWindowTitle("Notice");
  }

  msgBox->setWindowModality(Qt::NonModal);
  msgBox->show();
}

void callError(int message)
{
  QString intmessage= QString::number(message);
  QMessageBox msgBox;
  msgBox.setText("Error: " + intmessage);
  msgBox.setWindowTitle("Error");
  msgBox.exec();
}

void callFatalError(QString message, bool error_text)
{
  QMessageBox msgBox;
  if (error_text)
  {
    msgBox.setText("FATAL ERROR: " + message + "\n\nquitting application");
    msgBox.setWindowTitle("FATAL ERROR");
  }

  else
  {
    msgBox.setText(message);
    msgBox.setWindowTitle("Notice");
  }

  msgBox.exec();
  //appquit #T0D0
}


