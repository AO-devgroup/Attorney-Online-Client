#include "courtroom.h"
#include "ui_courtroom.h"
#include "config_handler.h"

Courtroom::Courtroom(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Courtroom)
{
  ui->setupUi(this);
  ui->background->setPixmap(QPixmap(getImagePath("courtroombackground.png")));
}

Courtroom::~Courtroom()
{
  delete ui;
}
