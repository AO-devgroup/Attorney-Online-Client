#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>
#include <QFont>
#include "courtroom.h"

namespace Ui {
class Lobby;
}

class Lobby : public QMainWindow
{
  Q_OBJECT

public:
  explicit Lobby(QWidget *parent = 0);
  ~Lobby();

public slots:
  void openCourtroomWindow();

private slots:
  void on_refresh_pressed();

  void on_refresh_released();

  void on_addtofav_pressed();

  void on_addtofav_released();

  void on_connect_pressed();

  void on_connect_released();

  void on_publicservers_clicked();

  void on_favorites_clicked();

private:
  Ui::Lobby *ui;
  Courtroom *mCourtroomWindow;
};

#endif // LOBBY_H
