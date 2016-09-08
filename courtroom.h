#ifndef COURTROOM_H
#define COURTROOM_H

#include <QMainWindow>
#include <QWindow>
#include <QMovie>
#include <QString>
#include <QLabel>
#include <QVector>
#include <QList>
#include <QSignalMapper>
#include <QSettings>
#include <QDebug>
#include <QModelIndex>
#include <QMediaPlayer>

#include "ui_courtroom.h"

#include "config_handler.h"
#include "error_handler.h"
#include "character_handler.h"
#include "emoteicon.h"
#include "charicon.h"
#include "datatypes.h"
#include "globals.h"
#include "file_handler.h"


namespace Ui {
class Courtroom;
}

class Courtroom : public QMainWindow
{
  Q_OBJECT


public:
  explicit Courtroom(QWidget *parent = 0);

  void setTheme();

  ~Courtroom();

private:
  Ui::Courtroom *ui;
  bool present_evidence = false;
  int objection_state{0};       // 0 is nothing, 1 is holdit, 2 is objection 3 is takethat

  int char_select_pages;
  int char_select_current_page;
  QString playerChar = "null";  //null in effect means spectator
  QVector<char_type> character_list; //custom datatype
  QVector<charicon* > charicon_list; //qpushbutton inherited(widget)
  QSignalMapper *mapper;

  void setCharSelect();
  void setCharSelectPage();

  int emote_pages;
  int emote_current_page;
  int emote_selected; //keeps track of which emote button is selected

  QVector<emote_type> emote_list; //custom datatype
  QVector<emoteicon* > emoteicon_list; //qpushbutton inherited(widget)
  QSignalMapper *emote_mapper;

  QVector<area_type> area_list;

  void construct_emotes();
  void setEmotes();
  void setEmotePage();

  QPushButton *emote_left_button;
  QPushButton *emote_right_button;

  //QSettings ini_charini;

  QMediaPlayer *songplayer;
  QStringList music_list;

  bool char_list_set = false;
  bool music_list_set = false;
  bool area_list_set = false;

  //true is ms, false is server
  bool ms_or_server_ooc = true;

  QString background_path;

  void enter_courtroom();

  void set_scene(QString p_bgimage, QString p_desk = "");

public slots:
  void set_character_list(QVector<char_type> &p_char_list);

  void set_music_list(QStringList &p_music_list);

  void set_area_list(QVector<area_type> &p_area_list);

  void handle_chatmessage(chatmessage_type &p_message);

  void handle_ms_message(QString p_message);
  void handle_ooc_message(QString p_message);

private slots:
  void charChoose(int i);

  void emote_choose(int local_emote_number);

  void on_holdit_clicked();

  void on_objection_clicked();

  void on_takethat_clicked();

  void on_present_clicked();

  void on_chatLine_returnPressed();

  void emote_right_clicked();

  void emote_left_clicked();

  void on_spectator_clicked();

  void on_musiclist_doubleClicked(const QModelIndex &index);

  void play_song(QString p_song_name);

  void on_charselect_left_clicked();
  void on_charselect_right_clicked();
  void on_changecharacter_clicked();

  void on_oocchatmessage_returnPressed();

  void on_ooc_master_clicked();

  void on_ooc_server_clicked();

signals:
  void entering_server();

  void chatmessage_requested(chatmessage_type &p_chatmessage);

  void song_requested(QString p_song_name);

  void ms_message_requested(QString p_packet);

  void ooc_message_requested(QString p_packet);


};

#endif // COURTROOM_H
