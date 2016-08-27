#include "courtroom.h"


Courtroom::Courtroom(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Courtroom)
{
  ui->setupUi(this);
  mapper = new QSignalMapper(this);
  this->setWindowTitle("Attorney Online");
}

Courtroom::~Courtroom()
{
  delete ui;
  delete mapper;
}

void Courtroom::initialize_courtroom()
{
  setCharSelect();
  show();
}

void Courtroom::set_character_list(QVector<char_type> &p_char_list)
{
  character_list = p_char_list;
  char_list_set = true;

  qDebug() << "set_character_list executed successfully";

  //HACK uncomment in production, commented out for debugging
  //if (music_list_set && background_set)
    setCharSelect();
}

void Courtroom::set_music_list(QStringList &p_music_list)
{
  music_list.clear();
  music_list = p_music_list;

  music_list_set = true;

  ui->musiclist->clear();

  for (int n_song = 0 ; n_song < music_list.size() ; ++n_song)
  {
    QString song_name = music_list.at(n_song);

    ui->musiclist->addItem(song_name);

    QString song_path = getBasePath() + "sounds/music/" + song_name;

    if (fileExists(song_path, true))
      ; //color background of ui->musiclist->at(n_song) green? check documentation and fix implementation #T0D0
    else
    {
      ; //background goes red #T0D0 as well
    }
  }

  if (char_list_set && background_set)
    setCharSelect();
}

void Courtroom::set_background(QString p_background)
{
  background_path = getBasePath() + "background/" + p_background + '/';
  background_set = true;

  if (music_list_set && char_list_set)
    setCharSelect();
}

void Courtroom::update_music_list()
{

}

void Courtroom::setTheme()
{
  QString background_path = g_theme_path + "courtroombackground.png";
  QString holdit_path = g_theme_path + "holdit_disabled.png";
  QString objection_path = g_theme_path + "objection_disabled.png";
  QString takethat_path = g_theme_path + "takethat_disabled.png";
  QString present_path = g_theme_path + "present_disabled.png";
  QString left_arrow_path = g_theme_path + "arrow_left.png";
  QString right_arrow_path = g_theme_path + "arrow_right.png";

  if (fileExists(background_path))
    ui->background->setPixmap(QPixmap(background_path));

  if (fileExists(holdit_path))
    ui->holdit->setStyleSheet("border-image:url(" + holdit_path + ")");

  if (fileExists(objection_path))
    ui->objection->setStyleSheet("border-image:url(" + objection_path + ")");

  if (fileExists(takethat_path))
    ui->takethat->setStyleSheet("border-image:url(" + takethat_path + ")");

  if (fileExists(present_path))
    ui->present->setStyleSheet("border-image:url(" + present_path + ")");

  if (fileExists(left_arrow_path))
    ui->emote_left->setStyleSheet("border-image:url(" + left_arrow_path + ")");

  if (fileExists(right_arrow_path))
    ui->emote_right->setStyleSheet("border-image:url(" + right_arrow_path + ")");

}

void Courtroom::enter_courtroom()
{
  //another failed attempt at optimizing
  /*
  for (charicon *f_charicon : charicon_list)
  {
    delete f_charicon;
  }

  charicon_list.clear();
  */

  update_music_list();
  setChar();
  setTheme();

  ui->charselect->hide();
}

void Courtroom::setChar()
{
//  LoadCharIni(playerChar); //This isn't needed anymore since we'll use QSettings from now on.

  //i. e. spectator
  if (playerChar == "null")
    return;

  setEmotes();

  emote_pressed = 1;

  if (emote_number == -1)
    callFatalError("failed to get emote_number (-1)");

  if ((emote_number % 10) == 0)             //we check if the amount of emotes is divisible by ten
    emote_pages = (emote_number / 10);
  else
    emote_pages = ((emote_number / 10) + 1);

  emote_current_page = 1;

  setEmotePage();

  ui->emote1->setStyleSheet("border-image:url(" + getEmoteIconPath(1) + "_on.png" + ")");

  ui->chatLine->show();
  ui->objection->show();
  ui->holdit->show();
  ui->takethat->show();
  ui->present->show();
}

void Courtroom::handle_chatmessage(chatmessage_type &p_message)
{
  ui->chatlog->appendPlainText(p_message.message);
}

void Courtroom::handle_ms_message(QString p_message)
{
  ui->oocmasterchat->appendPlainText(p_message);
}

void Courtroom::on_holdit_clicked()
{
  QString holdit_disabled_path = g_theme_path + "holdit_disabled.png";
  QString holdit_path = g_theme_path + "holdit.png";
  QString objection_path = g_theme_path + "objection_disabled.png";
  QString takethat_path = g_theme_path + "takethat_disabled.png";


  //if holdit is already enabled
  if (objection_state == 1)
  {
    objection_state = 0;
    if (fileExists(holdit_disabled_path))
      ui->holdit->setStyleSheet("border-image:url(" + holdit_disabled_path + ")");
  }
  else
  {
    objection_state = 1;
    if (fileExists(holdit_path))
      ui->holdit->setStyleSheet("border-image:url(" + holdit_path + ")");

    if (fileExists(objection_path))
      ui->objection->setStyleSheet("border-image:url(" + objection_path + ")");

    if (fileExists(takethat_path))
      ui->takethat->setStyleSheet("border-image:url(" + takethat_path + ")");
  }
}

void Courtroom::on_objection_clicked()
{
  QString objection_disabled_path = g_theme_path + "objection_disabled.png";
  QString objection_path = g_theme_path + "objection.png";
  QString holdit_path = g_theme_path + "holdit_disabled.png";
  QString takethat_path = g_theme_path + "takethat_disabled.png";


  //if objection is already enabled
  if (objection_state == 2)
  {
    objection_state = 0;
    if (fileExists(objection_disabled_path))
      ui->objection->setStyleSheet("border-image:url(" + objection_disabled_path + ")");
  }
  else
  {
    objection_state = 2;
    if (fileExists(objection_path))
      ui->objection->setStyleSheet("border-image:url(" + objection_path + ")");

    if (fileExists(holdit_path))
      ui->holdit->setStyleSheet("border-image:url(" + holdit_path + ")");

    if (fileExists(takethat_path))
      ui->takethat->setStyleSheet("border-image:url(" + takethat_path + ")");
  }
}

void Courtroom::on_takethat_clicked()
{
  QString takethat_disabled_path = g_theme_path + "takethat_disabled.png";
  QString takethat_path = g_theme_path + "takethat.png";
  QString holdit_path = g_theme_path + "holdit_disabled.png";
  QString objection_path = g_theme_path + "objection_disabled.png";


  //if takethat is already enabled
  if (objection_state == 3)
  {
    objection_state = 0;

    if (fileExists(takethat_disabled_path))
      ui->takethat->setStyleSheet("border-image:url(" + takethat_disabled_path + ")");
  }
  else
  {
    objection_state = 3;

    if (fileExists(takethat_path))
      ui->takethat->setStyleSheet("border-image:url(" + takethat_path + ")");

    if (fileExists(objection_path))
      ui->objection->setStyleSheet("border-image:url(" + objection_path + ")");

    if (fileExists(holdit_path))
      ui->holdit->setStyleSheet("border-image:url(" + holdit_path + ")");
  }
}

void Courtroom::on_present_clicked()
{
  QString present_on = g_theme_path + "present.png";
  QString present_off = g_theme_path + "present_disabled.png";

  if (present_evidence)
  {
    ui->present->setStyleSheet("border-image:url(" + present_off + ")");
    present_evidence = false;
  }

  else
  {
    ui->present->setStyleSheet("border-image:url(" + present_on + ")");
    present_evidence = true;
  }
}

void Courtroom::on_chatLine_returnPressed()
{
  QString chatMessage = ui->chatLine->text();
  ui->chatlog->appendPlainText(chatMessage);
  ui->chatLine->clear();

  ui->playingbackground->setPixmap(getBasePath() + "background/gs4/defenseempty.png");
  ui->desk->setPixmap(getBasePath() + "background/gs4/bancodefensa.png");
  ui->chatbubble->setPixmap(g_theme_path + "chat.png");

  QMovie *movie = new QMovie(getCharGifPath(playerChar, "(b)" + emote_list[getPressedEmote()].anim + ".gif"));
  ui->playingarea->setMovie(movie);

  movie->start();
}

void Courtroom::on_emote1_clicked()
{
  ui->chatLine->setFocus();

  int n = 1;

  setAllEmotesOff();

  ui->emote1->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote2_clicked()
{
  ui->chatLine->setFocus();

  int n = 2;

  setAllEmotesOff();

  ui->emote2->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote3_clicked()
{
  ui->chatLine->setFocus();

  int n = 3;

  setAllEmotesOff();

  ui->emote3->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote4_clicked()
{
  ui->chatLine->setFocus();

  int n = 4;

  setAllEmotesOff();

  ui->emote4->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote5_clicked()
{
  ui->chatLine->setFocus();

  int n = 5;

  setAllEmotesOff();

  ui->emote5->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote6_clicked()
{
  ui->chatLine->setFocus();

  int n = 6;

  setAllEmotesOff();

  ui->emote6->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote7_clicked()
{
  ui->chatLine->setFocus();

  int n = 7;

  setAllEmotesOff();

  ui->emote7->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote8_clicked()
{
  ui->chatLine->setFocus();

  int n = 8;

  setAllEmotesOff();

  ui->emote8->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote9_clicked()
{
  ui->chatLine->setFocus();

  int n = 9;

  setAllEmotesOff();

  ui->emote9->setStyleSheet("border-image:url(" + getEmoteIconPath(n) + "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote10_clicked()
{
  ui->chatLine->setFocus();

  int n = 10;

  setAllEmotesOff();

  ui->emote10->setStyleSheet("border-image:url(" + getEmoteIconPath(n) + "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote_left_clicked()
{
  --emote_current_page;
  setEmotePage();
}

void Courtroom::on_emote_right_clicked()
{
  ++emote_current_page;
  setEmotePage();
}


void Courtroom::on_spectator_clicked()
{
    ui->objection->hide();
    ui->holdit->hide();
    ui->takethat->hide();
    ui->present->hide();

    ui->emote10->hide();
    ui->emote9->hide();
    ui->emote8->hide();
    ui->emote7->hide();
    ui->emote6->hide();
    ui->emote5->hide();
    ui->emote4->hide();
    ui->emote3->hide();
    ui->emote2->hide();
    ui->emote1->hide();

    ui->emote_left->hide();
    ui->emote_right->hide();

    ui->chatLine->hide();

    ui->charselect->hide();
}

void Courtroom::on_charselect_left_clicked()
{
  --char_select_current_page;
  setCharSelectPage();
}

void Courtroom::on_charselect_right_clicked()
{
  ++char_select_current_page;
  setCharSelectPage();
}

void Courtroom::on_changecharacter_clicked()
{
  //T0D0
  //politely tell the server that we're not using our char anymore(playerChar)
  //(the network specification for this does not exist yet)

  char_select_current_page = 1;

  //setCharSelect();
  setCharSelectPage();
}

void Courtroom::on_musiclist_doubleClicked(const QModelIndex &index)
{
  //T0D0 set song_name to what is actually clicked
  QString song_name = music_list.at(index.row());

  song_requested(song_name);
}

void Courtroom::play_song(QString p_song_name)
{
  QString err_msg = "Song played: " + p_song_name;
  callError(err_msg);
  //T0D0, add implementation
  //QMusicPlayer.play() or something?
}

void Courtroom::on_oocchatmessage_returnPressed()
{
  QString name = ui->oocchatname->text();
  QString message = ui->oocchatmessage->text();
  QString packet = "CT#" + name + "#" + message + "#%";

  //no you cant send empty messages
  if ((name != "") && (message != ""))
  {
    ms_message_requested(packet);
    ui->oocchatmessage->clear();
  }
}
