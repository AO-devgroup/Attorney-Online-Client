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
}

void Courtroom::setChar()
{
  playerChar = "Vinyl";

  LoadCharIni(playerChar);

  emote_pressed = 1;

  emote_number = getEmoteNumber();

  if ((emote_number % 10) == 0) //we check if the amount of emotes is divisible by ten
    emote_pages = (emote_number / 10);
  else
    emote_pages = ((emote_number / 10) + 1);

  emote_current_page = 1;

  setEmotes();
}

void Courtroom::setEmotes()                 //called every time the emote page is changed
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

  int emotes_on_page;

  if(emote_pages < 1)                        //SANITY CHECK
    callError("amount of emote pages appear to be zero or negative");

  else if(emote_pages == 1)                  //first we check if there is only one page of emotes
    emotes_on_page = emote_number;

  else if(emote_current_page == emote_pages) //if not, then we check if we're on the last page
    emotes_on_page = (emote_number % 10);

  else if(emote_current_page < emote_pages)  //if not, we should be on a page that is not the last page
    emotes_on_page = 10;                     //conclusion: 10 emotes on the page

  else
    callFatalError("Something broke with the emotes idk");

  int max_emote = (((emote_pages - 1) * 10) + (emote_number % 10));

  QString path;

  switch(emotes_on_page)                     // !!!!!!INTENTIONAL FALLTHROUGH!!!!!!!!!!
  {
    case 10:
      path = getEmoteIconPath(playerChar, (max_emote-- + "_on"));
      if (fileExists(path))
        ui->emote10->setStyleSheet("border-image:url(" + path + ")");
        ui->emote10->show();

    case 9:
      path = getEmoteIconPath(playerChar, max_emote-- + "_on");
      if (fileExists(path))
        ui->emote9->setStyleSheet("border-image:url(" + path + ")");
        ui->emote9->show();

    case 8:
      path = getEmoteIconPath(playerChar, max_emote-- + "_on");
      if (fileExists(path))
        ui->emote8->setStyleSheet("border-image:url(" + path + ")");
        ui->emote8->show();

    case 7:
      path = getEmoteIconPath(playerChar, max_emote-- + "_on");
      if (fileExists(path))
        ui->emote7->setStyleSheet("border-image:url(" + path + ")");
        ui->emote7->show();

    case 6:
      path = getEmoteIconPath(playerChar, max_emote-- + "_on");
      if (fileExists(path))
        ui->emote6->setStyleSheet("border-image:url(" + path + ")");
        ui->emote6->show();

    case 5:
      path = getEmoteIconPath(playerChar, max_emote-- + "_on");
      if (fileExists(path))
        ui->emote5->setStyleSheet("border-image:url(" + path + ")");
        ui->emote5->show();

    case 4:
      path = getEmoteIconPath(playerChar, max_emote-- + "_on");
      if (fileExists(path))
        ui->emote4->setStyleSheet("border-image:url(" + path + ")");
        ui->emote4->show();

    case 3:
      path = getEmoteIconPath(playerChar, max_emote-- + "_on");
      if (fileExists(path))
        ui->emote3->setStyleSheet("border-image:url(" + path + ")");
        ui->emote3->show();

    case 2:
      path = getEmoteIconPath(playerChar, max_emote-- + "_on");
      if (fileExists(path))
        ui->emote2->setStyleSheet("border-image:url(" + path + ")");
        ui->emote2->show();

    case 1:
      path = getEmoteIconPath(playerChar, max_emote + "_on");
      if (fileExists(path))
        ui->emote1->setStyleSheet("border-image:url(" + path + ")");
        ui->emote1->show();

    default:
      callFatalError("something broke hilariously. blame the terrible developers");
  }




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
  ui->plainTextEdit->setPlainText(chatMessage);
  ui->chatLine->clear();
}
