#include "courtroom.h"


Courtroom::Courtroom(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Courtroom)
{
  ui->setupUi(this);
  mapper = new QSignalMapper(this);
  emote_mapper = new QSignalMapper(this);
  songplayer = new QMediaPlayer(this);
  charmovie = new QMovie(this);
  speedlinesmovie = new QMovie(this);

  construct_emotes();
  this->setWindowTitle("Attorney Online");
}

Courtroom::~Courtroom()
{
  delete ui;
  delete mapper;
  delete emote_mapper;
  delete emote_left_button;
  delete emote_right_button;
  delete songplayer;
}

//called on character_list_received from network handler
void Courtroom::set_character_list(QVector<char_type> &p_char_list)
{
  character_list = p_char_list;
  char_list_set = true;  
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
}

void Courtroom::set_area_list(QVector<area_type> &p_area_list)
{
  area_list.clear();
  area_list = p_area_list;

  area_list_set = true;
}

//called whenever DONE#% is received
void Courtroom::go_to_charselect()
{
  //the ONLY thing this does is hide the lobby window!! dont worry about it!!
  entering_server();



  setCharSelect();
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
    emote_left_button->setStyleSheet("border-image:url(" + left_arrow_path + ")");

  if (fileExists(right_arrow_path))
    emote_right_button->setStyleSheet("border-image:url(" + right_arrow_path + ")");

  emote_left_button->hide();
  emote_right_button->hide();

}

void Courtroom::set_character(QString p_character, int p_mod)
{
  switch (p_mod)
  {
  case 0:
    playerChar = p_character;
    enter_courtroom();
    break;
  case 1:
    ui->charError->setText("This character is already taken.");
    break;
  case 2:
    ui->charError->setText("Wrong password");
    break;
  default:
    callError("Unexpected reply from server! Expected 0, 1 or 2 in OC packet, received " + p_mod);

  }

}

void Courtroom::enter_courtroom()
{
  setTheme();

  if (playerChar == "null")
  {
    ui->chatLine->hide();
    ui->objection->hide();
    ui->holdit->hide();
    ui->takethat->hide();
    ui->present->hide();
    emote_left_button->hide();
    emote_right_button->hide();

    for(emoteicon *i_icon : emoteicon_list)
    {
      i_icon->hide();
    }
  }
  else
  {
    setEmotes();
    setEmotePage();
  }

  ui->oocserverchat->hide();
  ui->chatLine->clear();
  ui->chatLine->show();
  ui->chatLine->setFocus();

  ui->charselect->hide();
}

void Courtroom::on_chatLine_returnPressed()
{
  QString f_message = ui->chatLine->text();
  if(f_message == "")
  {
    return;
  }

  chatmessage_type f_chatmessage;

  QFile char_ini(getCharPath(playerChar) + "char.ini");
  if (!char_ini.open(QIODevice::ReadOnly))
  {
    callError("failed to open " + getCharPath(playerChar) + "char.ini for reading.");
  }

  QTextStream in(&char_ini);
  QString f_side = "";

  for(; !in.atEnd() ;)
  {
    QString line = in.readLine();
    if (line.startsWith("side = "))
    {
      f_side = line.remove(0, 7);
      break;
    }
  }

  if (f_side == "")
    callError("could not find side = in char.ini");

  emote_type f_emote = emote_list.at(emote_selected);

  f_chatmessage.message = f_message;
  f_chatmessage.character = playerChar;
  f_chatmessage.side = f_side;

  f_chatmessage.sfx_name = f_emote.sfx_name;
  f_chatmessage.pre_emote = f_emote.preanim;
  f_chatmessage.emote = f_emote.anim;
  f_chatmessage.emote_modifier = f_emote.mod;

  f_chatmessage.objection_modifier = objection_state;
  f_chatmessage.realization = realization_state;
  f_chatmessage.text_color = text_color_state;
  f_chatmessage.evidence = evidence_state;

  //legacy mode sends the message in the old format, check network handler for more info
  if (legacy_mode)
    legacy_chatmessage_requested(f_chatmessage);

  else
    chatmessage_requested(f_chatmessage);




  ui->chatLine->clear();
}

void Courtroom::set_scene(QString p_side)
{
  QString default_path = getBasePath() + "background/default/";

  QString f_background_path = background_path;
  QString f_default_background_path = default_path;

  QString f_speedlines_path = g_theme_path;
  QString f_default_speedlines_path = getBasePath() + "themes/default/";

  QString f_desk_path = background_path;
  QString f_default_desk_path = default_path;

  if (p_side == "wit")
  {
    f_background_path += "witnessempty.png";
    f_default_background_path += "witnessempty.png";
    f_speedlines_path += "prosecution_speedlines.gif";
    f_default_speedlines_path += "prosecution_speedlines.gif";
    f_desk_path += "estrado.png";
    f_default_desk_path += "estrado.png";
  }
  else if (p_side == "def")
  {
    f_background_path += "defenseempty.png";
    f_default_background_path += "defenseempty.png";
    f_speedlines_path += "defense_speedlines.gif";
    f_default_speedlines_path += "defense_speedlines.gif";
    f_desk_path += "bancodefensa.png";
    f_default_desk_path += "bancodefensa.png";
  }
  else if (p_side == "pro")
  {
    f_background_path += "prosecutorempty.png";
    f_default_background_path += "prosecutorempty.png";
    f_speedlines_path += "prosecution_speedlines.gif";
    f_default_speedlines_path += "prosecution_speedlines.gif";
    f_desk_path += "bancoacusacion.png";
    f_default_desk_path += "bancoacusacion.png";
  }
  else if (p_side == "jud")
  {
    f_background_path += "judgestand.png";
    f_default_background_path += "judgestand.png";
    f_speedlines_path += "defense_speedlines.gif";
    f_default_speedlines_path += "defense_speedlines.gif";
    f_desk_path = "";
    f_default_desk_path = "";
  }
  else if (p_side == "hld")
  {
    f_background_path += "helperstand.png";
    f_default_background_path += "helperstand.png";
    f_speedlines_path += "defense_speedlines.gif";
    f_default_speedlines_path += "defense_speedlines.gif";
    f_desk_path = "";
    f_default_desk_path = "";
  }
  else if (p_side == "hlp")
  {
    f_background_path += "prohelperstand.png";
    f_default_background_path += "prohelperstand.png";
    f_speedlines_path += "prosecution_speedlines.gif";
    f_default_speedlines_path += "prosecution_speedlines.gif";
    f_desk_path = "";
    f_default_desk_path = "";
  }
  else
  {
    callError("Something went hilariously wrong. (Invalid side: " + p_side + ")");
    return;
  }

  if (fileExists(f_background_path, true))
    ui->playingbackground->setPixmap(f_background_path);
  else if (fileExists(f_default_background_path, true))
    ui->playingbackground->setPixmap(f_default_background_path);
  else
    ui->playingbackground->clear();

  if (fileExists(f_speedlines_path, true))
    speedlinesmovie->setFileName(f_speedlines_path);
  else if (fileExists(f_default_speedlines_path, true))
    speedlinesmovie->setFileName(f_default_speedlines_path);
  else
  {
    ;
  }

  if (fileExists(f_desk_path, true))
    ui->desk->setPixmap(f_desk_path);
  else if (fileExists(f_default_desk_path, true))
    ui->desk->setPixmap(f_default_desk_path);
  else
    ui->desk->clear();
}

void Courtroom::handle_chatmessage(chatmessage_type &p_message)
{ 
  QString showname = getShowname(p_message.character);
  //QTextCursor bruh = new QTextCursor(ui->chatlog);

  //bruh.setPosition(0);

  ui->chatlog->appendPlainText(showname + ": " + p_message.message);

  qDebug() << "executing set_scene";
  set_scene(p_message.side);
  qDebug() << "set_scene executed";

  if(fileExists(g_theme_path + "chat.png"))
    ui->chatbubble->setPixmap(g_theme_path + "chat.png");

  else
    ui->chatbubble->setPixmap(getBasePath() + "background/default/chat.png");

  ui->chattext->setPlainText(p_message.message);
  ui->chattext->show();
  ui->charname->setText(showname);
  ui->chatbubble->show();

  //QMovie *movie = new QMovie(getCharGifPath(p_message.character, "(b)" + p_message.emote + ".gif"));
  //ui->playingarea->setMovie(movie);
  if (p_message.emote_modifier == 5)
  {
    ui->playingbackground->setMovie(speedlinesmovie);
    speedlinesmovie->start();
  }
  QString gif_path = getCharGifPath(p_message.character, "(b)" + p_message.emote + ".gif");

  charmovie->setFileName(gif_path);
  ui->playingarea->setMovie(charmovie);
  charmovie->start();

  qDebug() << "handle_chatmessage executed";
}

void Courtroom::handle_ms_message(QString p_message)
{
  ui->oocmasterchat->appendPlainText(p_message);
}

void Courtroom::handle_ooc_message(QString p_message)
{
  ui->oocserverchat->appendPlainText(p_message);
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

void Courtroom::emote_left_clicked()
{
  --emote_current_page;
  setEmotePage();
}

void Courtroom::emote_right_clicked()
{
  qDebug() << "emote_right_clicked called";
  ++emote_current_page;
  setEmotePage();
}


void Courtroom::on_spectator_clicked()
{
    playerChar = "null";

    enter_courtroom();
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
  request_packet("FC#%");
}

void Courtroom::on_musiclist_doubleClicked(const QModelIndex &index)
{
  QString song_name = music_list.at(index.row());

  song_requested(song_name);
}

void Courtroom::play_song(QString p_song_name)
{
  QString song_path = getBasePath() + "sounds/music/" + p_song_name;

  if (fileExists(song_path))
  {
    songplayer->setMedia(QUrl::fromLocalFile(song_path));
    songplayer->setVolume(50);
    songplayer->play();
  }

  //assume "stop.mp3" or something
  else
  {
    songplayer->setVolume(0);
  }
}

void Courtroom::on_oocchatmessage_returnPressed()
{
  QString name = ui->oocchatname->text();
  QString message = ui->oocchatmessage->text();
  QString packet = "CT#" + name + "#" + message + "#%";

  //no you cant send empty messages
  if ((name != "") && (message != ""))
  {
    //true is ms toggled
    if (ms_or_server_ooc)
      ms_message_requested(packet);
    else
      ooc_message_requested(packet);

    ui->oocchatmessage->clear();
  }
}

void Courtroom::on_ooc_master_clicked()
{
  ms_or_server_ooc = true;
  ui->oocserverchat->hide();
  ui->oocmasterchat->show();
}

void Courtroom::on_ooc_server_clicked()
{
  ms_or_server_ooc = false;
  ui->oocmasterchat->hide();
  ui->oocserverchat->show();
}
