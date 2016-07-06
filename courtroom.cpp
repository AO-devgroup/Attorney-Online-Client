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
  //set emote buttons #T0D0
  playerChar = "Vinyl";
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
  ui->plainTextEdit->appendPlainText("ayy lmao");
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
  //callError("BOIS");
  QString chatMessage = ui->chatLine->text();
  ui->plainTextEdit->setPlainText(chatMessage);
  ui->chatLine->clear();
}
