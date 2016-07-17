#include "charicon.h"


charicon::charicon(int x_pos, int y_pos, QString character, QWidget *parent)
{
  m_character = character;

  QString path = getCharPath(character) + "char_icon.png";

  //LEGACY SUPPORT, for ao classic filestructure
  QString legacy_path = getBasePath() + "misc/DemoThings/" + character + "_char_icon.png";

  //we also need a lowercase version for the legacy support. again because of inconsistent naming

  QString legacy_path_lower = getBasePath() + "misc/DemoThings/" + character.toLower() + "_char_icon.png";

  this->setParent(parent);
  this->resize(60, 60);
  this->move(x_pos, y_pos);
  if (fileExists(path, true))
  {
    this->setStyleSheet("border-image:url(" + path + ")");
    this->show();
  }
  else if (fileExists(legacy_path, true))
  {
    this->setStyleSheet("border-image:url(" + path + ")");
    this->show();
  }
  else if (fileExists(legacy_path_lower, true))
  {
    this->setStyleSheet("border-image:url(" + legacy_path_lower + ")");
    this->show();
  }
  //if the char icon could not be found we add a neat text label to help the user :)
  else
  {
    this->setText(character);
    this->show();
  }
}

void charicon::leaveEvent(QEvent * e)
{
  setFlat(true);
  QPushButton::leaveEvent(e);
}

void charicon::enterEvent(QEvent * e)
{
  //ui->char_selector.char_selector.move(10, 10);
  //Courtroom.char_selector.show();
  setFlat(false);
  QPushButton::enterEvent(e);
}

void charicon::clicked()
{
  m_is_selected = true;
}

charicon::~charicon()
{
  delete this;
}
