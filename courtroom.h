#ifndef COURTROOM_H
#define COURTROOM_H

#include <QMainWindow>
#include <QMovie>
#include <QString>
#include <QLabel>

#include "ui_courtroom.h"

#include "config_handler.h"
#include "error_handler.h"
#include "character_handler.h"
#include "networking.h"
#include "charicon.h"

namespace Ui {
class Courtroom;
}

class Courtroom : public QMainWindow
{
  Q_OBJECT

public:
  explicit Courtroom(QWidget *parent = 0);
  void setTheme();                         //sets images according to theme in config.ini
  void setChar();                          //loads appropriate char.ini into the global namespace
  void setCharSelect();
  QLabel char_selector;
  ~Courtroom();

private slots:
  /*
  void on_holdit_pressed();

  void on_holdit_released();

  void on_objection_pressed();

  void on_objection_released();

  void on_takethat_pressed();

  void on_takethat_released();
  */
  void on_holdit_clicked();

  void on_objection_clicked();

  void on_takethat_clicked();

  void on_present_clicked();

  void on_chatLine_returnPressed();

  void on_emote1_clicked();

  void on_emote2_clicked();

  void on_emote3_clicked();

  void on_emote4_clicked();

  void on_emote5_clicked();

  void on_emote6_clicked();

  void on_emote7_clicked();

  void on_emote8_clicked();

  void on_emote9_clicked();

  void on_emote10_clicked();

  void on_emote_right_clicked();

  void on_emote_left_clicked();

  void on_spectator_clicked();

private:
  Ui::Courtroom *ui;
  bool present_evidence = false;
  int objection_state{0};       // 0 is nothing, 1 is holdit, 2 is objection 3 is takethat
  QString playerChar = "null";  //in effect means spectator
  int emote_number;
  int emote_pages;
  int emote_current_page;
  int emote_pressed;      //keeps track of which emote button is pressed
  void setEmotePage();       //sets emote images
  void setAllEmotesOff();
  QString getEmoteIconPath(int emotenumber);
  QStringList emote_list{"emote_list element 0"};
  void setEmotes();
  int getPressedEmote();
  QStringList char_select_list;
};

#endif // COURTROOM_H
