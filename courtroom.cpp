#include "courtroom.h"
#include "ui_courtroom.h"
#include "config_handler.h"

Courtroom::Courtroom(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Courtroom)
{
  ui->setupUi(this);
  ui->background->setPixmap(QPixmap(getImagePath("courtroombackground.png")));
  ui->holdit->setStyleSheet("border-image:url(" + getImagePath("holdit.png") + ")");
  ui->objection->setStyleSheet("border-image:url(" + getImagePath("objection.png") + ")");
  ui->takethat->setStyleSheet("border-image:url(" + getImagePath("takethat.png") + ")");
}

Courtroom::~Courtroom()
{
  delete ui;
}

void Courtroom::on_holdit_pressed()
{
  ui->holdit->setStyleSheet("border-image:url(" + getImagePath("holdit_pressed.png") + ")");
}

void Courtroom::on_holdit_released()
{
  ui->holdit->setStyleSheet("border-image:url(" + getImagePath("holdit.png") + ")");
  QMovie *movie = new QMovie(getCharGifPath("(b)normal.gif"));
  ui->playingarea->setMovie(movie);
  movie->start();
  ui->plainTextEdit->appendPlainText("ayy lmao");
}

void Courtroom::on_objection_pressed()
{
  ui->objection->setStyleSheet("border-image:url(" + getImagePath("objection_pressed.png") + ")");
}

void Courtroom::on_objection_released()
{
  ui->objection->setStyleSheet("border-image:url(" + getImagePath("objection.png") + ")");
  QMovie *movie = new QMovie(getCharGifPath("(a)normal.gif"));
  ui->playingarea->setMovie(movie);
  movie->start();
  ui->plainTextEdit->appendPlainText("ayy lmao");
}

void Courtroom::on_takethat_pressed()
{
  ui->takethat->setStyleSheet("border-image:url(" + getImagePath("takethat_pressed.png") + ")");
}

void Courtroom::on_takethat_released()
{
  ui->takethat->setStyleSheet("border-image:url(" + getImagePath("takethat.png") + ")");
}
