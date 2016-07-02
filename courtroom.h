#ifndef COURTROOM_H
#define COURTROOM_H

#include <QMainWindow>
#include <QMovie>

namespace Ui {
class Courtroom;
}

class Courtroom : public QMainWindow
{
  Q_OBJECT

public:
  explicit Courtroom(QWidget *parent = 0);
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
};

#endif // COURTROOM_H
