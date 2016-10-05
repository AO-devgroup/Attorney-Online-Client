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
#include <QTextCursor>
#include <QBrush>
#include <QColor>
#include <QTimer>
#include <QScrollBar>
#include <QCloseEvent>
#include <QTime>

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

  //0 is no realization(bling), 1 is
  int realization_state = 0;
  //0 is nothing, 1 is holdit, 2 is objection 3 is takethat
  int objection_state = 0;
  //0 is no evidence, the rest is NYI
  int evidence_state = 0;
  //0 is white, 1 is blue, 2 is green, 3 is orange and 4 is red
  int text_color_state = 0;

  int defense_health = 10;
  int prosecution_health = 10;

  int char_select_pages;
  int char_select_current_page;
  QString playerChar = "null";  //null in effect means spectator
  QVector<char_type> character_list; //custom datatype
  QVector<charicon* > charicon_list; //qpushbutton inherited(widget)
  QSignalMapper *mapper;
  QVector<int> taken_list;

  void construct_charselect();
  //void setCharSelect();
  void setCharSelectPage();

  int emote_pages;
  int emote_current_page;
  int emote_selected; //keeps track of which emote button is selected

  QVector<emote_type> emote_list; //custom datatype
  QVector<emoteicon* > emoteicon_list; //qpushbutton inherited(widget)
  QSignalMapper *emote_mapper;

  QVector<area_type> area_list;
  QVector<int> area_taken_list;

  void construct_emotes();
  void setEmotes();
  void setEmotePage();

  QPushButton *emote_left_button;
  QPushButton *emote_right_button;

  int emotes_on_page;

  //QSettings ini_charini;

  QMediaPlayer *musicplayer;
  QMediaPlayer *sfxplayer;
  QMediaPlayer *blipplayer;
  QMediaPlayer *blipplayer2;
  QMediaPlayer *guardplayer;

  QStringList music_list;
  QStringList ui_music_list;

  bool char_list_set = false;
  bool taken_list_set = false;
  bool done_received = false;
  bool music_list_set = false;
  bool area_list_set = false;
  bool area_taken_list_set = false;

  //true is ms, false is server
  bool ms_or_server_ooc = true;

  QString background_path;

  bool legacy_mode = false;

  QMovie *charmovie;
  QMovie *speedlinesmovie;
  QMovie *testimonymovie;
  QMovie *objectionmovie;
  QTimer *chattimer;
  QTimer *sfxdelaytimer;
  QTimer *realizationtimer;
  //QTimer *animtimer;

  int animframe = 0;
  QVector<QImage> mirror_anim;

  QTime *debugtime;

  int chatpos = 0;

  chatmessage_type current_chatmessage;

  QString char_gender = "male";

  //0 is nothing, 1 is WT, 2 is between WT and CE and 3 is CE
  //needed because gifs are dum
  int testimonystate = 0;

  //0 is during preanim, 1 is talking and 2 is idle after talking.
  int charmovie_state = 2;

  QVector<bool> mutelist;
  bool show_mutelist = false;

  const int chat_timing = 60;

  bool muted = false;
  bool in_court = false;

  int m_cid = -1;

  QString get_background_path(QString p_background_image);

  void enter_courtroom();

  void set_area_ui();

  void set_flipped_animation(QString p_gif_path);

  void handle_chatmessage2();

  void closeEvent(QCloseEvent *event);

public slots:
  void set_character_list(QVector<char_type> &p_char_list);

  void set_taken_list(QVector<int> &p_taken_list);

  void set_music_list(QStringList &p_music_list);

  void set_area_list(QVector<area_type> &p_area_list);

  void set_area_taken_list(QVector<int> &p_area_taken_list);

  void go_to_charselect();

  void set_character(int p_character, int p_mod);

  //void handle_chatmessage(chatmessage_type &p_message);
  void handle_chatmessage();

  void handle_ms_message(QString p_message);
  void handle_ooc_message(QString p_message);

  void handle_server_packet(QString p_packet);

  void handle_server_disconnect();

private slots:
  void testimony_gif_framechange(int p_frame);

  void objection_gif_framechange(int p_frame);

  void char_gif_framechange(int p_frame);

  void charChoose(int i);

  void emote_choose(int local_emote_number);

  void chat_tick();

  void realization_done();

  void on_holdit_clicked();

  void on_objection_clicked();

  void on_takethat_clicked();

  void on_present_clicked();

  void on_chatLine_returnPressed();

  void emote_right_clicked();

  void emote_left_clicked();

  void on_spectator_clicked();

  void on_musiclist_doubleClicked(const QModelIndex &index);

  void on_charselect_left_clicked();
  void on_charselect_right_clicked();
  void on_changecharacter_clicked();

  void on_oocchatmessage_returnPressed();

  void on_ooc_master_clicked();

  void on_ooc_server_clicked();

  void on_defminus_clicked();

  void on_defplus_clicked();

  void on_prominus_clicked();

  void on_proplus_clicked();

  void on_musicsearch_textEdited(const QString &p_text);

  void on_ooc_toggle_clicked();

  void on_realization_clicked();

  void on_reload_theme_clicked();

  void on_witnesstestimony_clicked();

  void on_crossexamination_clicked();

  void on_arealist_clicked(const QModelIndex &index);

  void on_arealist_doubleClicked(const QModelIndex &index);

  void on_callmod_clicked();

  void on_textcolor_activated(int index);

  void on_mute_clicked();

  void on_mutelist_clicked(const QModelIndex &index);

  void on_prebox_clicked();

  void on_flipbox_clicked();

  void play_sfx();

  void on_musicslider_valueChanged(int value);

  void on_sfxslider_valueChanged(int value);

  void on_blipslider_valueChanged(int value);

  void on_backtolobby_clicked();

signals:
  void entering_server();

  void leaving_server();

  void chatmessage_requested(chatmessage_type &p_chatmessage);
  void legacy_chatmessage_requested(chatmessage_type &p_chatmessage);

  void character_requested(int p_character, QString p_password);

  void song_requested(QString p_song_name);

  void ms_message_requested(QString p_packet);

  void ooc_message_requested(QString p_packet);

  void request_packet(QString p_packet);

  void close_socket_request();

  void request_quit();


};

#endif // COURTROOM_H
