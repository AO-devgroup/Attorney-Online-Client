#ifndef COURTROOM_H
#define COURTROOM_H

#include <QMainWindow>
#include <QMovie>
#include <QString>

#include "ui_courtroom.h"

#include "config_handler.h"
#include "error_handler.h"
#include "character_handler.h"

namespace Ui {
class Courtroom;
}

class Courtroom : public QMainWindow
{
  Q_OBJECT

public:
  explicit Courtroom(QWidget *parent = 0);
  void setTheme();
  void setChar();
  ~Courtroom();

private slots:
  void on_holdit_pressed();

  void on_holdit_released();

  void on_objection_pressed();

  void on_objection_released();

  void on_takethat_pressed();

  void on_takethat_released();

  void on_present_clicked();

  void on_chatLine_returnPressed();

private:
  Ui::Courtroom *ui;
  bool present_evidence = false;
  QString playerChar = "null";
};

#endif // COURTROOM_H
