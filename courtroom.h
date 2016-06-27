#ifndef COURTROOM_H
#define COURTROOM_H

#include <QMainWindow>
//#include "lobby.h"

namespace Ui {
class Courtroom;
}

class Courtroom : public QMainWindow
{
  Q_OBJECT

public:
  explicit Courtroom(QWidget *parent = 0);
  ~Courtroom();

private:
  Ui::Courtroom *ui;
};

#endif // COURTROOM_H
