#ifndef COURTROOM_H
#define COURTROOM_H

#include <QMainWindow>
#include <QMovie>
#include <QString>
#include <QLabel>
#include <QVector>
#include <QList>
#include <QSignalMapper>
#include <QSettings>

#include "ui_courtroom.h"

#include "config_handler.h"
#include "error_handler.h"
#include "character_handler.h"
#include "networking.h"
#include "charicon.h"
#include "datatypes.h"

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
  void setCharSelectPage();
  //QLabel char_selector;
  QVector<charicon* > charicon_list;
  QVector<QLabel* > char_taken_list;

  ~Courtroom();

public slots:
  void handleCharicon(QString character);

private:
  Ui::Courtroom *ui;
  bool present_evidence = false;
  int objection_state{0};       // 0 is nothing, 1 is holdit, 2 is objection 3 is takethat
  QString playerChar = "null";  //in effect means spectator
  int emote_number;
  int emote_pages;
  int emote_current_page;
  int emote_pressed;      //keeps track of which emote button is pressed
  void setEmotes();
  void setEmotePage();
  void setAllEmotesOff();
  QString getEmoteIconPath(int emotenumber);
  QVector<emote_type> emote_list;
  //QStringList emote_list {"emote_list element 0"};
  int getPressedEmote();
  QStringList char_select_list;
  int char_select_pages;
  int char_select_current_page;
  int char_amount;
  QVector<int> chars_taken;
  void setTakenChars();
  QSettings ini_charini;

private slots:
  void charChoose(int i);

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

  void on_charselect_left_clicked();
  void on_charselect_right_clicked();
  void on_changecharacter_clicked();
};

#endif // COURTROOM_H
