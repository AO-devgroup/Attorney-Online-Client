#include "courtroom.h"
#include "ui_courtroom.h"

Courtroom::Courtroom(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Courtroom)
{
  ui->setupUi(this);
}

Courtroom::~Courtroom()
{
  delete ui;
}
