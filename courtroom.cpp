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

  construct_charselect();
  construct_emotes();
  this->setWindowTitle("Attorney Online");

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
  delete songplayer;
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
}

//called whenever DONE#% is received
void Courtroom::go_to_charselect()
{
  m_cid = -1;

  for(emoteicon *f_icon : emoteicon_list)
  {
    f_icon->hide();
  }

  emote_left_button->hide();
  emote_right_button->hide();

  //the ONLY thing this does is hide the lobby window!! dont worry about it!!
  entering_server();

  show();
  ui->charselect->show();
}

void Courtroom::setTheme()
{
  QString background_path = g_theme_path + "courtroombackground.png";
  QString present_path = g_theme_path + "present_disabled.png";
  QString left_arrow_path = g_theme_path + "arrow_left.png";
  QString right_arrow_path = g_theme_path + "arrow_right.png";

  if (fileExists(background_path))
    ui->background->setPixmap(QPixmap(background_path));

  if (fileExists(present_path))
    ui->present->setStyleSheet("border-image:url(" + present_path + ")");

  if (fileExists(left_arrow_path))
    emote_left_button->setStyleSheet("border-image:url(" + left_arrow_path + ")");

  if (fileExists(right_arrow_path))
    emote_right_button->setStyleSheet("border-image:url(" + right_arrow_path + ")");

  ui->holdit->setStyleSheet("border-image:url(" + get_image_path("holdit.png") + ")");
  ui->objection->setStyleSheet("border-image:url(" + get_image_path("objection.png") + ")");
  ui->takethat->setStyleSheet("border-image:url(" + get_image_path("takethat.png") + ")");

  ui->defminus->setStyleSheet("border-image:url(" + get_image_path("defminus.png") + ")");
  ui->defplus->setStyleSheet("border-image:url(" + get_image_path("defplus.png") + ")");
  ui->prominus->setStyleSheet("border-image:url(" + get_image_path("prominus.png") + ")");
  ui->proplus->setStyleSheet("border-image:url(" + get_image_path("proplus.png") + ")");
  ui->realization->setStyleSheet("border-image:url(" + get_image_path("realization.png") + ")");
  ui->mute->setStyleSheet("border-image:url(" + get_image_path("mute.png") + ")");

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
  else if (fileExists(f_default_desk_path))
    ui->desk->setPixmap(f_default_desk_path);
  else
    ui->desk->clear();
}

void Courtroom::handle_chatmessage(chatmessage_type &p_message)
{ 
  QString showname = getShowname(p_message.character);

  QString f_message = (p_message.message).replace("<num>", "#");

  ui->chatlog->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);
  ui->chatlog->insertPlainText(showname + ": " + f_message + '\n');
  ui->desk->show();

  set_scene(p_message.side);

  if(fileExists(g_theme_path + "chat.png"))
    ui->chatbubble->setPixmap(g_theme_path + "chat.png");

  else
    ui->chatbubble->setPixmap(getBasePath() + "background/default/chat.png");

  ui->chattext->setPlainText(f_message);
  ui->chattext->show();
  ui->charname->setText(showname);
  ui->chatbubble->show();

  //QMovie *movie = new QMovie(getCharGifPath(p_message.character, "(b)" + p_message.emote + ".gif"));
  //ui->playingarea->setMovie(movie);
  if (p_message.emote_modifier == 5)
  {
    speedlinesmovie->stop();
    ui->desk->hide();
    ui->playingbackground->setMovie(speedlinesmovie);
    speedlinesmovie->start(); 
  }

  QString gif_path = getCharGifPath(p_message.character, "(b)" + p_message.emote + ".gif");

  charmovie->stop();
  charmovie->setFileName(gif_path);
  ui->playingarea->setMovie(charmovie);
  charmovie->start();

  qDebug() << "handle_chatmessage executed";
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
  QString song_name = music_list.at(index.row());

  song_requested(song_name);
}

void Courtroom::play_song(QString p_song_name)
{
  QString song_path = getBasePath() + "sounds/music/" + p_song_name;

  if (fileExists(song_path, true))
  {
    songplayer->setMedia(QUrl::fromLocalFile(song_path));
    songplayer->setVolume(50);
    songplayer->play();
  }

  //assume "stop.mp3" or something
  else
  {
    songplayer->stop();
  }
}

void Courtroom::handle_server_packet(QString &p_packet)
{
  QStringList packet_contents = p_packet.split("#", QString::SplitBehavior(QString::SkipEmptyParts));

  QString header = packet_contents.at(0);

  if (header == "HP"){
    QString side = packet_contents.at(1);
    QString str_hp_amount = packet_contents.at(2);
    int hp_amount = str_hp_amount.toInt();

    if (hp_amount > 5 || hp_amount < 0)
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
  if (defense_health >= 5)
    request_packet("HP#def#5#%");
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
  if (prosecution_health >= 5)
    request_packet("HP#pro#5#%");
  else
    request_packet("HP#pro#" + QString::number(prosecution_health + 1) + "#%");
}

void Courtroom::on_musicsearch_textEdited(const QString &p_text)
{

  ui->musiclist->clear();

  QVector<QString> new_list;

  for (int index = 0 ; index < music_list.size() ; ++index)
  {
    QString song = music_list.at(index);

    if (song.contains(p_text))
    {
      ui->musiclist->addItem(song);
      new_list.append(song);
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
