#include "courtroom.h"


Courtroom::Courtroom(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Courtroom)
{
  ui->setupUi(this);
  this->setWindowTitle("Attorney Online");
}

void Courtroom::setTheme()
{
  LoadConfig();

  QString background_path = getImagePath("courtroombackground.png");
  QString holdit_path = getImagePath("holdit.png");
  QString objection_path = getImagePath("objection.png");
  QString takethat_path = getImagePath("takethat.png");
  QString present_path = getImagePath("present_pressed.png");
  QString left_arrow_path = getImagePath("arrow_left.png");
  QString right_arrow_path = getImagePath("arrow_right.png");

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

void Courtroom::setChar()
{
  playerChar = "Phoenix";

  LoadCharIni(playerChar);

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
}

void Courtroom::setEmotes()
{
  bool found_emotions = false;
  QString line;
  emote_number = -1;

  for(int line_number{0} ; line_number < g_char_ini.size() ; ++line_number)
  {
    line = g_char_ini.at(line_number);

    //we are satisified if the line starts with target string
    //in case someone adds a space and wonders why things break
    if (line.startsWith("[Emotions]"))
      found_emotions = true;

    if (line.startsWith("number = ") && found_emotions)
    {
      //removes "number = " from the start of the string
      QString newline = line.remove(0, 9);

      //SANITY CHECK
      if (newline.toInt() < 1)
        callFatalError("number of emotes appear to be zero or negative");

      emote_number = newline.toInt();
    }

    if (!(emote_number == -1) && line.startsWith("1 = "))
    {

      for(int emote_n{1} ; emote_n <= emote_number ; ++emote_n)
      {
        int current_line_n = line_number + emote_n - 1;
        QString current_line = g_char_ini[current_line_n];
        QStringList line_list = current_line.split("#");

        emote_list.insert(emote_n, line_list[2]);
      }
      break;
    }


    //in the unlikely event that we reach EOF
    if (line_number == (g_char_ini.size() - 1))
    {
      callError("could not find [Emotions] in char.ini");
    }
  }
}

//called every time the emote page is changed

void Courtroom::setEmotePage()
{
  //first we hide everything

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

  int emotes_on_page = -1;

  if(emote_pages < 1)                        //SANITY CHECK
    callError("amount of emote pages appear to be zero or negative");

  else if(emote_pages == 1)                  //first we check if there is only one page of emotes
    emotes_on_page = emote_number;

  else if(emote_current_page == emote_pages) //if not, then we check if we're on the last page
    emotes_on_page = (emote_number % 10);

  else if(emote_current_page < emote_pages)  //if not, we should be on a page that is not the last page
    emotes_on_page = 10;                     //conclusion: 10 emotes on the page

  else if(emotes_on_page == -1)
    callFatalError("emotes_on_page was not set properly (-1)");

  else
    callFatalError("Something broke with the emotes idk. blame the terrible developers."
                   "seriously, though. emotes_on_page failed to set properly. who knows why."
                   "this error should never appear ever ever");

  //here we check if the left and right arrows need to appear

  //anything higher than the first page must have the left arrow
  if (emote_current_page > 1)
    ui->emote_left->show();

  //as long as the max amount of pages is higher than the current one, right arrow is shown
  if (emote_current_page < emote_pages)
    ui->emote_right->show();


  /////////////////////////////////////////////////////////////////////////////////////////
  // !!!!!!INTENTIONAL FALLTHROUGH!!!!!!!!!!
  // the way this works is that if there are ten emotes on the page, all emotes will be set
  // if 9, then everything below case 9 will be executed etc.
  // remember that all emotes are hidden earlier ^
  // if a case is matched, the rest of the case checks will be IGNORED
  // that is how a switch fallthrough works, you're welcome
  /////////////////////////////////////////////////////////////////////////////////////////

  QString path;

  switch(emotes_on_page)
  {
    case 10:
      path = getEmoteIconPath(10) + "_off.png";
      if (fileExists(path))
      {
        ui->emote10->setStyleSheet("border-image:url(" + path + ")");
        ui->emote10->show();
      }

    case 9:
      path = getEmoteIconPath(9) + "_off.png";
      if (fileExists(path))
      {
        ui->emote9->setStyleSheet("border-image:url(" + path + ")");
        ui->emote9->show();
      }

    case 8:
      path = getEmoteIconPath(8) + "_off.png";
      if (fileExists(path))
      {
        ui->emote8->setStyleSheet("border-image:url(" + path + ")");
        ui->emote8->show();
      }

    case 7:
      path = getEmoteIconPath(7) + "_off.png";
      if (fileExists(path))
      {
        ui->emote7->setStyleSheet("border-image:url(" + path + ")");
        ui->emote7->show();
      }

    case 6:
      path = getEmoteIconPath(6) + "_off.png";
      if (fileExists(path))
      {
        ui->emote6->setStyleSheet("border-image:url(" + path + ")");
        ui->emote6->show();
      }

    case 5:
      path = getEmoteIconPath(5) + "_off.png";
      if (fileExists(path))
      {
        ui->emote5->setStyleSheet("border-image:url(" + path + ")");
        ui->emote5->show();
      }

    case 4:
      path = getEmoteIconPath(4) + "_off.png";
      if (fileExists(path))
      {
        ui->emote4->setStyleSheet("border-image:url(" + path + ")");
        ui->emote4->show();
      }

    case 3:
      path = getEmoteIconPath(3) + "_off.png";
      if (fileExists(path))
      {
        ui->emote3->setStyleSheet("border-image:url(" + path + ")");
        ui->emote3->show();
      }

    case 2:
      path = getEmoteIconPath(2) + "_off.png";
      if (fileExists(path))
      {
        ui->emote2->setStyleSheet("border-image:url(" + path + ")");
        ui->emote2->show();
      }

    case 1:
      path = getEmoteIconPath(1) + "_off.png";
      if (fileExists(path))
      {
        ui->emote1->setStyleSheet("border-image:url(" + path + ")");
        ui->emote1->show();
      }
  }

}

//this is some topkek bs code right here but i couldnt find a better way to do it

void Courtroom::setAllEmotesOff()
{
  QString path;

  path = getEmoteIconPath(1) + "_off.png";
  ui->emote1->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(2) + "_off.png";
  ui->emote2->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(3) + "_off.png";
  ui->emote3->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(4) + "_off.png";
  ui->emote4->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(5) + "_off.png";
  ui->emote5->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(6) + "_off.png";
  ui->emote6->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(7) + "_off.png";
  ui->emote7->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(8) + "_off.png";
  ui->emote8->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(9) + "_off.png";
  ui->emote9->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(10) + "_off.png";
  ui->emote10->setStyleSheet("border-image:url(" + path + ")");

}

//i forgot how but this works somehow
int Courtroom::getPressedEmote()
{
  return (emote_pressed + (10 * (emote_current_page - 1)));
}

QString Courtroom::getEmoteIconPath(int emotenumber)
{
  QString str_emotenumber = QString::number(emotenumber + (10 * (emote_current_page - 1)));

  //we need to check both uppercase and lowercase B's because the files are inconsistently named

  QString smallb = getCharPath(playerChar) + "emotions/button" + str_emotenumber;
  QString bigb = getCharPath(playerChar) + "emotions/Button" + str_emotenumber;

  //true as param makes the check quiet and does not throw an error if it fails
  //we also need to check both on and off for reasons
  if (fileExists(smallb + "_off.png", true) && fileExists(smallb + "_on.png", true))
    return smallb;

  else if (fileExists(bigb + "_off.png", true) && fileExists(bigb + "_on.png", true))
    return bigb;

  //at this point, we know the file doesnt exist, but we return this and the caller handles the error
  else
    return smallb;
}

Courtroom::~Courtroom()
{
  delete ui;
}

void Courtroom::on_holdit_pressed()
{
  QString path = getImagePath("holdit_pressed.png");

  if (fileExists(path))
    ui->holdit->setStyleSheet("border-image:url(" + path + ")");
}

void Courtroom::on_holdit_released()
{
  QString path = getImagePath("holdit.png");

  if (fileExists(path))
    ui->holdit->setStyleSheet("border-image:url(" + path + ")");

  QMovie *movie = new QMovie(getCharGifPath(playerChar,"(b)normal.gif"));
  ui->playingarea->setMovie(movie);
  movie->start();
  ui->plainTextEdit->appendPlainText(g_char_ini[0]);
}

void Courtroom::on_objection_pressed()
{
  QString path = getImagePath("objection_pressed.png");

  if (fileExists(path))
    ui->objection->setStyleSheet("border-image:url(" + path + ")");
}

void Courtroom::on_objection_released()
{
  QString path = getImagePath("objection.png");

  if (fileExists(path))
    ui->objection->setStyleSheet("border-image:url(" + path + ")");

  QMovie *movie = new QMovie(getCharGifPath(playerChar, "(a)normal.gif"));
  ui->playingarea->setMovie(movie);
  movie->start();
  ui->plainTextEdit->appendPlainText("ayy lmao");
}

void Courtroom::on_takethat_pressed()
{
  QString path = getImagePath("takethat_pressed.png");

  if (fileExists(path))
    ui->takethat->setStyleSheet("border-image:url(" + path + ")");
}

void Courtroom::on_takethat_released()
{
  QString path = getImagePath("takethat.png");

  if (fileExists(path))
    ui->takethat->setStyleSheet("border-image:url(" + path + ")");
}

void Courtroom::on_present_clicked()
{
  QString present_on = getImagePath("present.png");
  QString present_off = getImagePath("present_pressed.png");

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
  ui->plainTextEdit->appendPlainText(chatMessage);
  ui->chatLine->clear();

  ui->playingbackground->setPixmap(getBasePath() + "background/gs4/defenseempty.png");
  ui->desk->setPixmap(getBasePath() + "background/gs4/bancodefensa.png");
  ui->chatbubble->setPixmap(getImagePath("chat.png"));

  QMovie *movie = new QMovie(getCharGifPath(playerChar, "(b)" + emote_list[getPressedEmote()] + ".gif"));
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

  ui->emote9->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote10_clicked()
{
  ui->chatLine->setFocus();

  int n = 10;

  setAllEmotesOff();

  ui->emote10->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
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

