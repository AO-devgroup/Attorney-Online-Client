#include "courtroom.h"


Courtroom::Courtroom(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Courtroom)
{
  ui->setupUi(this);
  mapper = new QSignalMapper(this);
  emote_mapper = new QSignalMapper(this);
  musicplayer = new QMediaPlayer(this);
  sfxplayer = new QMediaPlayer(this);
  blipplayer = new QMediaPlayer(this);
  charmovie = new QMovie(this);
  speedlinesmovie = new QMovie(this);
  testimonymovie = new QMovie(this);
  objectionmovie = new QMovie(this);
  chattimer = new QTimer(this);

  connect(testimonymovie, SIGNAL(frameChanged(int)), this, SLOT(testimony_gif_framechange(int)));

  connect(objectionmovie, SIGNAL(frameChanged(int)), this, SLOT(objection_gif_framechange(int)));

  connect(charmovie, SIGNAL(frameChanged(int)), this, SLOT(char_gif_framechange(int)));

  connect(chattimer, SIGNAL(timeout()), this, SLOT(chat_tick()));

  construct_charselect();
  construct_emotes();
  this->setWindowTitle("Attorney Online");

  musicplayer->setVolume(50);
  sfxplayer->setVolume(50);
  blipplayer->setVolume(50);

  ui->playingarea->setMovie(charmovie);
  ui->objectiongif->setMovie(objectionmovie);
  ui->testimony->setMovie(testimonymovie);
  ui->playingbackground->setMovie(speedlinesmovie);

  //so when we show() and hide() charselect, children follow suit
  ui->charselect_left->setParent(ui->charselect);
  ui->charselect_right->setParent(ui->charselect);
  ui->spectator->setParent(ui->charselect);
  ui->charpass->setParent(ui->charselect);
  ui->charError->setParent(ui->charselect);

  ui->charselect->raise();
  ui->charselect_left->raise();
  ui->charselect_right->raise();
  ui->spectator->raise();
  ui->charpass->raise();
  ui->charError->raise();
}

Courtroom::~Courtroom()
{
  delete ui;
  delete mapper;
  delete emote_mapper;
  delete emote_left_button;
  delete emote_right_button;
  delete musicplayer;
}

void Courtroom::set_music_list(QStringList &p_music_list)
{
  music_list.clear();
  music_list = p_music_list;
  ui_music_list = music_list;

  music_list_set = true;

  ui->musiclist->clear();

  for (int n_song = 0 ; n_song < music_list.size() ; ++n_song)
  {
    QString song_name = music_list.at(n_song);

    ui->musiclist->addItem(song_name);

    QString song_path = getBasePath() + "sounds/music/" + song_name;

    if (fileExists(song_path, true))
      ui->musiclist->item(n_song)->setBackground(Qt::green);
    else
      ui->musiclist->item(n_song)->setBackground(Qt::red);
  }
}

void Courtroom::set_area_list(QVector<area_type> &p_area_list)
{
  area_list.clear();
  area_list = p_area_list;

  area_list_set = true;

  if (!area_taken_list_set)
    return;

  set_area_ui();
}

void Courtroom::set_area_taken_list(QVector<int> &p_area_taken_list)
{
  area_taken_list.clear();
  area_taken_list = p_area_taken_list;

  area_taken_list_set = true;

  if (!area_list_set)
    return;

  set_area_ui();
}

void Courtroom::set_area_ui()
{
  ui->arealist->clear();

  for (int n_area = 0 ; n_area < area_list.size() ; ++n_area)
  {
    QString area_name = area_list.at(n_area).name;
    int area_population = area_taken_list.at(n_area);

    if(area_list.at(n_area).passworded)
      ui->arealist->addItem(area_name + " (" + QString::number(area_population) + ")*");
    else
      ui->arealist->addItem(area_name + " (" + QString::number(area_population) + ")");
  }
}

//called whenever DONE#% is received
void Courtroom::go_to_charselect()
{
  m_cid = -1;

  done_received = true;

  for(emoteicon *f_icon : emoteicon_list)
  {
    f_icon->hide();
  }

  emote_left_button->hide();
  emote_right_button->hide();

  ui->charselect->show();

  if (char_list_set && taken_list_set)
  {
    setCharSelectPage();
    entering_server();
    show();
  }
}

void Courtroom::setTheme()
{
  ui->background->setPixmap(QPixmap(get_image_path("courtroombackground.png")));

  ui->present->setStyleSheet("border-image:url(" + get_image_path("present_disabled.png") + ")");

  emote_left_button->setStyleSheet("border-image:url(" + get_image_path("arrow_left.png") + ")");

  emote_right_button->setStyleSheet("border-image:url(" + get_image_path("arrow_right.png") + ")");

  ui->holdit->setStyleSheet("border-image:url(" + get_image_path("holdit.png") + ")");
  ui->objection->setStyleSheet("border-image:url(" + get_image_path("objection.png") + ")");
  ui->takethat->setStyleSheet("border-image:url(" + get_image_path("takethat.png") + ")");

  ui->defminus->setStyleSheet("border-image:url(" + get_image_path("defminus.png") + ")");
  ui->defplus->setStyleSheet("border-image:url(" + get_image_path("defplus.png") + ")");
  ui->prominus->setStyleSheet("border-image:url(" + get_image_path("prominus.png") + ")");
  ui->proplus->setStyleSheet("border-image:url(" + get_image_path("proplus.png") + ")");
  ui->realization->setStyleSheet("border-image:url(" + get_image_path("realization.png") + ")");
  ui->mute->setStyleSheet("border-image:url(" + get_image_path("mute.png") + ")");

  ui->witnesstestimony->setStyleSheet("border-image:url(" + get_image_path("witnesstestimony.png") + ")");
  ui->crossexamination->setStyleSheet("border-image:url(" + get_image_path("crossexamination.png") + ")");

  ui->defense_bar->setStyleSheet("border-image:url(" + get_image_path("defensebar10.png") + ")");
  ui->prosecution_bar->setStyleSheet("border-image:url(" + get_image_path("prosecutionbar10.png") + ")");

  ui->areapreview->hide();
  ui->deskpreview->hide();
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
  if (playerChar != "null")
  {
    QFile char_ini(getCharPath(playerChar) + "char.ini");
    if (!char_ini.open(QIODevice::ReadOnly))
    {
      callError("failed to open " + getCharPath(playerChar) + "char.ini for reading.");
    }

    QTextStream in(&char_ini);
    QString f_side = "";

    while(!in.atEnd())
    {
      QString line = in.readLine();
      if (line.startsWith("side = "))
      {
        f_side = line.remove(0, 7);
        break;
      }

      else if (line.startsWith("side ="))
      {
        f_side = line.remove(0, 6);
        break;
      }

      else if (line.startsWith("side= "))
      {
        f_side = line.remove(0, 6);
        break;
      }

      else if (line.startsWith("side="))
      {
        f_side = line.remove(0, 5);
        break;
      }
    }


    if (f_side == "")
      callError("could not find side = in char.ini");

    if (f_side == "jud")
    {
      ui->witnesstestimony->show();
      ui->crossexamination->show();
      ui->proplus->show();
      ui->prominus->show();
      ui->defplus->show();
      ui->defminus->show();
    }
    else
    {
      ui->witnesstestimony->hide();
      ui->crossexamination->hide();
      ui->proplus->hide();
      ui->prominus->hide();
      ui->defplus->hide();
      ui->defminus->hide();
    }
  }

  if (playerChar == "null")
  {
    ui->chatLine->hide();
    ui->objection->hide();
    ui->holdit->hide();
    ui->takethat->hide();
    ui->present->hide();
    ui->witnesstestimony->hide();
    ui->crossexamination->hide();
    ui->proplus->hide();
    ui->prominus->hide();
    ui->defplus->hide();
    ui->defminus->hide();
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
    ui->holdit->show();
    ui->objection->show();
    ui->takethat->show();
    ui->chatLine->show();
    ui->chatLine->setFocus();
  }

  ui->oocserverchat->hide();
  ui->chatLine->clear();

  setTheme();

  ui->charselect->hide();
}

void Courtroom::on_chatLine_returnPressed()
{
  QString f_message = ui->chatLine->text();

  //no you cant send empty messages
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

    else if (line.startsWith("side ="))
    {
      f_side = line.remove(0, 6);
      break;
    }

    else if (line.startsWith("side= "))
    {
      f_side = line.remove(0, 6);
      break;
    }

    else if (line.startsWith("side="))
    {
      f_side = line.remove(0, 5);
      break;
    }
  }

  if (f_side == "")
    callError("could not find side = in char.ini");

  emote_type f_emote = emote_list.at(emote_selected);

  f_chatmessage.message = f_message.replace("#", "<num>");
  f_chatmessage.character = playerChar.replace("#", "<num>");
  f_chatmessage.side = f_side.replace("#", "<num>");

  f_chatmessage.sfx_name = f_emote.sfx_name;
  f_chatmessage.pre_emote = f_emote.preanim;
  f_chatmessage.emote = f_emote.anim;
  f_chatmessage.emote_modifier = f_emote.mod;

  f_chatmessage.objection_modifier = objection_state;
  f_chatmessage.realization = realization_state;
  f_chatmessage.text_color = text_color_state;
  f_chatmessage.evidence = evidence_state;
  f_chatmessage.cid = m_cid;

  //legacy mode sends the message in the old format, check network handler for more info
  if (legacy_mode)
    legacy_chatmessage_requested(f_chatmessage);

  else
    chatmessage_requested(f_chatmessage);

  objection_state = 0;
  ui->holdit->setStyleSheet("border-image:url(" + get_image_path("holdit.png") + ")");
  ui->objection->setStyleSheet("border-image:url(" + get_image_path("objection.png") + ")");
  ui->takethat->setStyleSheet("border-image:url(" + get_image_path("takethat.png") + ")");

  realization_state = 0;
  ui->realization->setStyleSheet("border-image:url(" + get_image_path("realization.png") + ")");


  ui->chatLine->clear();
}

void Courtroom::set_scene(QString p_side)
{
  QString default_path = getBasePath() + "background/gs4/";

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
    f_background_path += "witnessempty.png";
    f_default_background_path += "witnessempty.png";
    f_speedlines_path += "prosecution_speedlines.gif";
    f_default_speedlines_path += "prosecution_speedlines.gif";
    f_desk_path += "estrado.png";
    f_default_desk_path += "estrado.png";
  }

  if (fileExists(f_background_path, true))
    ui->playingbackground->setPixmap(f_background_path);
  else if (fileExists(f_default_background_path))
    ui->playingbackground->setPixmap(f_default_background_path);
  else
    ui->playingbackground->clear();

  if (fileExists(f_speedlines_path, true))
    speedlinesmovie->setFileName(f_speedlines_path);
  else if (fileExists(f_default_speedlines_path))
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

//void Courtroom::handle_chatmessage(chatmessage_type &p_message)
void Courtroom::handle_chatmessage()
{ 
  //current_chatmessage = p_message;

  QString char_path = getBasePath() + "characters/";

  switch(current_chatmessage.objection_modifier)
  {
  case 0:
    objectionmovie->stop();
    handle_chatmessage2(); //rest of the stuff that needs to happen is called here
    break;
  case 1:
    objectionmovie->stop();
    objectionmovie->setFileName(get_image_path("holdit.gif"));
    //ui->objectiongif->setMovie(objectionmovie);
    sfxplayer->setMedia(QUrl::fromLocalFile(char_path + '/' + current_chatmessage.character + "/holdit.wav"));
    sfxplayer->play();
    objectionmovie->start(); //handle_chatmessage2 is called when this is done playing, continuing the logic
    break;
  case 2:
    objectionmovie->stop();
    objectionmovie->setFileName(get_image_path("objection.gif"));
    //ui->objectiongif->setMovie(objectionmovie);
    sfxplayer->setMedia(QUrl::fromLocalFile(char_path + '/' + current_chatmessage.character + "/objection.wav"));
    sfxplayer->play();
    objectionmovie->start();
    break;
  case 3:
    objectionmovie->stop();
    objectionmovie->setFileName(get_image_path("takethat.gif"));
    //ui->objectiongif->setMovie(objectionmovie);
    sfxplayer->setMedia(QUrl::fromLocalFile(char_path + '/' + current_chatmessage.character + "/takethat.wav"));
    sfxplayer->play();
    objectionmovie->start();
    break;
  default:
    handle_chatmessage2();
    ;
  }
}

void Courtroom::handle_chatmessage2()
{
  QString showname = getShowname(current_chatmessage.character);

  QString f_message = (current_chatmessage.message).replace("<num>", "#");

  ui->chatlog->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);
  ui->chatlog->insertPlainText(showname + ": " + f_message + '\n');
  ui->desk->show();

  if (current_chatmessage.sfx_name != "1")
  {
    sfxplayer->stop();
    sfxplayer->setMedia(QUrl::fromLocalFile(getBasePath() + "sounds/general/" + current_chatmessage.sfx_name + ".wav"));
    sfxplayer->play();
  }

  switch(current_chatmessage.text_color)
  {
  case 0:
    ui->chattext->setStyleSheet("QPlainTextEdit{color: white;}");
    //ui->chatLine->setStyleSheet("QLineEdit{color: white;}");
    break;
  case 1:
    ui->chattext->setStyleSheet("QPlainTextEdit{color: blue;}");
    //ui->chatLine->setStyleSheet("color: blue;");
    break;
  case 2:
    ui->chattext->setStyleSheet("QPlainTextEdit{color: rgb(0, 255, 0);}");
    //ui->chatLine->setStyleSheet("QLineEdit{color: rgb(0, 255, 0);}");
    break;
  case 3:
    ui->chattext->setStyleSheet("QPlainTextEdit{color: orange;}");
    //ui->chatLine->setStyleSheet("QLineEdit{color: orange;}");
    break;
  case 4:
    ui->chattext->setStyleSheet("QPlainTextEdit{color: red;}");
    //ui->chatLine->setStyleSheet("QLineEdit{color: red;}");
    break;
  default:
    ui->chattext->setStyleSheet("QPlainTextEdit{color: white;}");
    //ui->chatLine->setStyleSheet("QLineEdit{color: white;}");
  }

  set_scene(current_chatmessage.side);

  if(fileExists(g_theme_path + "chat.png"))
    ui->chatbubble->setPixmap(g_theme_path + "chat.png");

  else
    ui->chatbubble->setPixmap(getBasePath() + "background/default/chat.png");

  //ui->chattext->setPlainText(f_message);

  ui->chattext->clear();

  ui->chattext->show();
  ui->charname->setText(showname);
  ui->chatbubble->show();

  QString gif_path = getCharGifPath(current_chatmessage.character, "(b)" + current_chatmessage.emote + ".gif");
  QString gif_preanim_path = getCharGifPath(current_chatmessage.character, current_chatmessage.pre_emote + ".gif");

  charmovie->stop();
  speedlinesmovie->stop();



  switch (current_chatmessage.emote_modifier)
  {
  case 0:
    if (current_chatmessage.objection_modifier == 0)
    {
      charmovie->setFileName(gif_path);
      charmovie_state = 1;
    }
    else
    {
      charmovie->setFileName(gif_preanim_path);
      charmovie_state = 0;
    }
    qDebug() << "case 0";
    charmovie->start();
    break;
  case 1:
    charmovie->setFileName(gif_preanim_path);
    charmovie_state = 0;
    charmovie->start();
    qDebug() << "case 1";
    break;
  case 5:
    ui->desk->hide();
    charmovie->setFileName(gif_path);
    charmovie_state = 1;
    //ui->playingbackground->setMovie(speedlinesmovie);
    speedlinesmovie->start();
    charmovie->start();
    qDebug() << "case 5";
    break;
  default:
    ;
  }
}

void Courtroom::handle_ms_message(QString p_message)
{
  QString message = p_message.replace("<num>", "#");

  ui->oocmasterchat->appendPlainText(message);
}

void Courtroom::handle_ooc_message(QString p_message)
{
  QString message = p_message.replace("<num>", "#");

  ui->oocserverchat->appendPlainText(message);
}

void Courtroom::on_holdit_clicked()
{
  //if holdit is already enabled
  if (objection_state == 1)
  {
    objection_state = 0;

    ui->holdit->setStyleSheet("border-image:url(" + get_image_path("holdit.png") + ")");
  }
  else
  {
    objection_state = 1;

    ui->holdit->setStyleSheet("border-image:url(" + get_image_path("holdit_selected.png") + ")");
    ui->objection->setStyleSheet("border-image:url(" + get_image_path("objection.png") + ")");
    ui->takethat->setStyleSheet("border-image:url(" + get_image_path("takethat.png") + ")");
  }

  ui->chatLine->setFocus();
}

void Courtroom::on_objection_clicked()
{
  //if objection is already enabled
  if (objection_state == 2)
  {
    objection_state = 0;

    ui->objection->setStyleSheet("border-image:url(" + get_image_path("objection.png") + ")");
  }
  else
  {
    objection_state = 2;

    ui->objection->setStyleSheet("border-image:url(" + get_image_path("objection_selected.png") + ")");
    ui->holdit->setStyleSheet("border-image:url(" + get_image_path("holdit.png") + ")");
    ui->takethat->setStyleSheet("border-image:url(" + get_image_path("takethat.png") + ")");
  }

  ui->chatLine->setFocus();
}

void Courtroom::on_takethat_clicked()
{
  //if takethat is already enabled
  if (objection_state == 3)
  {
    objection_state = 0;

    ui->takethat->setStyleSheet("border-image:url(" + get_image_path("takethat.png") + ")");
  }
  else
  {
    objection_state = 3;

    ui->takethat->setStyleSheet("border-image:url(" + get_image_path("takethat_selected.png") + ")");
    ui->objection->setStyleSheet("border-image:url(" + get_image_path("objection.png") + ")");
    ui->holdit->setStyleSheet("border-image:url(" + get_image_path("holdit.png") + ")");
  }

  ui->chatLine->setFocus();
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

  ui->chatLine->setFocus();
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
  QString song_name = ui_music_list.at(index.row());
  QString str_cid = QString::number(m_cid);

  request_packet("MC#" + song_name + "#" + str_cid + "#%");

  //song_requested(song_name);
}

void Courtroom::play_song(QString p_song_name)
{
  QString song_path = getBasePath() + "sounds/music/" + p_song_name;

  if (fileExists(song_path, true))
  {
    musicplayer->setMedia(QUrl::fromLocalFile(song_path));
    musicplayer->play();
  }

  //assume "stop.mp3" or something
  else
  {
    musicplayer->stop();
  }
}

void Courtroom::handle_server_packet(QString p_packet)
{
  QStringList packet_contents = p_packet.split("#");

  QString header = packet_contents.at(0);

  if (header == "MS")
  {
    current_chatmessage.pre_emote = packet_contents.at(2);
    current_chatmessage.character = packet_contents.at(3);
    current_chatmessage.emote = packet_contents.at(4);
    current_chatmessage.message = packet_contents.at(5);
    current_chatmessage.side = packet_contents.at(6);
    current_chatmessage.sfx_name = packet_contents.at(7);
    current_chatmessage.emote_modifier = packet_contents.at(8).toInt();
    current_chatmessage.objection_modifier = packet_contents.at(9).toInt();
    current_chatmessage.realization = packet_contents.at(10).toInt();
    current_chatmessage.text_color = packet_contents.at(11).toInt();
    current_chatmessage.evidence = packet_contents.at(12).toInt();
    current_chatmessage.cid = packet_contents.at(13).toInt();

    handle_chatmessage();
  }

  else if (header == "HP")
  {
    QString side = packet_contents.at(1);
    QString str_hp_amount = packet_contents.at(2);
    int hp_amount = str_hp_amount.toInt();

    if (hp_amount > 10 || hp_amount < 0)
      return;

    if (side == "def")
    {
      ui->defense_bar->setPixmap(get_image_path("defensebar" + str_hp_amount + ".png"));
      defense_health = hp_amount;
    }

    if (side == "pro")
    {
      ui->prosecution_bar->setPixmap(get_image_path("prosecutionbar" + str_hp_amount + ".png"));
      prosecution_health = hp_amount;
    }
  }

  else if (header == "RT")
  {
    if (packet_contents.size() < 3)
    {
      callError("Malformed packet; " + p_packet);
      return;
    }

    QString argument = packet_contents.at(1);

    if (argument == "testimony1")
    {
      testimonystate = 1;
      testimonymovie->stop();
      sfxplayer->stop();
      //ui->testimony->setMovie(testimonymovie);
      sfxplayer->setMedia(QUrl::fromLocalFile(getBasePath() + "sounds/general/sfx-testimony2.wav"));
      testimonymovie->setFileName(get_image_path("witnesstestimony.gif"));
      sfxplayer->play();
      testimonymovie->start();
    }

    else if (argument == "testimony2")
    {
      testimonystate = 3;
      testimonymovie->stop();
      sfxplayer->stop();
      //ui->testimony->setMovie(testimonymovie);
      sfxplayer->setMedia(QUrl::fromLocalFile(getBasePath() + "sounds/general/sfx-testimony.wav"));
      testimonymovie->setFileName(get_image_path("crossexamination.gif"));
      sfxplayer->play();
      testimonymovie->start();
    }
  }
  else if (header == "OA")
  {
    if (packet_contents.at(2) == "0")
    {
      int bg_index = packet_contents.at(1).toInt();

      background_path = getBasePath() + "background/" + area_list.at(bg_index).background + "/";
      //more things to do for area switch probably #T0D0
    }
    else if (packet_contents.at(2) == "1")
      callError("Wrong password :v(");
  }
}

void Courtroom::on_oocchatmessage_returnPressed()
{
  QString name = ui->oocchatname->text().replace("#", "<num>");
  QString message = ui->oocchatmessage->text().replace("#", "<num>");
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

void Courtroom::on_defminus_clicked()
{
  if (defense_health <= 0)
    request_packet("HP#def#0#%");
  else
    request_packet("HP#def#" + QString::number(defense_health - 1) + "#%");
}

void Courtroom::on_defplus_clicked()
{
  if (defense_health >= 10)
    request_packet("HP#def#10#%");
  else
    request_packet("HP#def#" + QString::number(defense_health + 1) + "#%");
}

void Courtroom::on_prominus_clicked()
{
  if (prosecution_health <= 0)
    request_packet("HP#pro#0#%");
  else
    request_packet("HP#pro#" + QString::number(prosecution_health - 1) + "#%");
}

void Courtroom::on_proplus_clicked()
{
  if (prosecution_health >= 10)
    request_packet("HP#pro#10#%");
  else
    request_packet("HP#pro#" + QString::number(prosecution_health + 1) + "#%");
}

void Courtroom::on_musicsearch_textEdited(const QString &p_text)
{

  ui->musiclist->clear();
  ui_music_list.clear();

  QVector<QString> new_list;

  for (int index = 0 ; index < music_list.size() ; ++index)
  {
    QString song = music_list.at(index);

    if (song.contains(p_text))
    {
      ui->musiclist->addItem(song);
      new_list.append(song);
      ui_music_list.append(song);
    }
  }

  for (int index = 0 ; index < new_list.size() ; ++index)
  {
    QString song_path = getBasePath() + "sounds/music/" + new_list.at(index);

    if (fileExists(song_path, true))
      ui->musiclist->item(index)->setBackground(Qt::green);
    else
      ui->musiclist->item(index)->setBackground(Qt::red);

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

void Courtroom::on_ooc_toggle_clicked()
{
  if (ms_or_server_ooc)
  {
    ui->ooc_toggle->setText("Server");
    ms_or_server_ooc = false;
    ui->oocmasterchat->hide();
    ui->oocserverchat->show();
  }
  else
  {
    ui->ooc_toggle->setText("Master");
    ms_or_server_ooc = true;
    ui->oocserverchat->hide();
    ui->oocmasterchat->show();
  }
}

void Courtroom::on_realization_clicked()
{
  if (realization_state == 0)
  {
    realization_state = 1;
    ui->realization->setStyleSheet("border-image:url(" + get_image_path("realization_pressed.png") + ")");
  }
  else
  {
    realization_state = 0;
    ui->realization->setStyleSheet("border-image:url(" + get_image_path("realization.png") + ")");
  }
}

void Courtroom::on_reload_theme_clicked()
{
  set_theme_path();

  setTheme();
}

void Courtroom::on_witnesstestimony_clicked()
{
  request_packet("RT#testimony1#%");
}

void Courtroom::on_crossexamination_clicked()
{
  request_packet("RT#testimony2#%");
}

void Courtroom::on_musicslider_sliderMoved(int p_position)
{
  musicplayer->setVolume(p_position);
}

void Courtroom::on_sfxslider_sliderMoved(int p_position)
{
  sfxplayer->setVolume(p_position);
}

void Courtroom::on_blipslider_sliderMoved(int p_position)
{
  blipplayer->setVolume(p_position);
}

void Courtroom::on_arealist_clicked(const QModelIndex &index)
{
  if (area_list_set && area_taken_list_set)
  {
    QString background = area_list.at(index.row()).background;

    ui->areapreview->setPixmap(get_background_path(background, "defenseempty.png"));
    ui->deskpreview->setPixmap(get_background_path(background, "bancodefensa.png"));

    ui->areapreview->show();
    ui->deskpreview->show();
  }
}

void Courtroom::on_arealist_doubleClicked(const QModelIndex &index)
{ 
  QString n_area = QString::number(index.row());

  request_packet("AA#" + n_area + "#" + ui->areapassword->text() + "#%");
}

void Courtroom::testimony_gif_framechange(int p_frame)
{
  if (p_frame == (testimonymovie->frameCount()-1))
  {
    if (testimonystate == 1)
    {
      //so that the testimony blinks between WT and CE
      testimonymovie->stop();
      testimonymovie->setFileName(get_image_path("testimony.gif"));
      testimonymovie->start();
      testimonystate = 2;
    }

    else if (testimonystate == 2)
      ;
    else
      testimonymovie->stop();
  }
}

void Courtroom::objection_gif_framechange(int p_frame)
{
  if (p_frame >= (objectionmovie->frameCount()-1))
  {
    objectionmovie->stop();
    handle_chatmessage2();
  }
}

void Courtroom::char_gif_framechange(int p_frame)
{
  if (p_frame == (charmovie->frameCount()-1))
  {
    if (charmovie_state == 0)
    {
      //this is called when the preanimation has played once
      charmovie_state = 1;
      chattimer->stop();
      charmovie->stop();
      charmovie->setFileName(getCharGifPath(current_chatmessage.character, ("(b)" + current_chatmessage.emote + ".gif")));
      //"character talking gif" starts here
      charmovie->start();
      chattimer->start(100);
    }
  }

}

void Courtroom::on_callmod_clicked()
{
  request_packet("ZZ#%");
}

void Courtroom::on_textcolor_activated(int index)
{
  text_color_state = index;
}

void Courtroom::chat_tick()
{

  sfxplayer->stop();
  sfxplayer->setMedia(QUrl::fromLocalFile(getBasePath() + "sounds/general/sfx-blipmale.wav"));
  sfxplayer->play();
  ui->chattext->insertPlainText("a");
}
