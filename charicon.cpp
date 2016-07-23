#include "charicon.h"

#include "courtroom.h"

charicon::charicon()
{

}

charicon::charicon(int x_pos, int y_pos, QWidget *parent)
{
  this->setParent(parent);
  this->resize(60, 60);
  this->move(x_pos, y_pos);
  //connect(this, SIGNAL (clicked()), this, SLOT (handleButton()));
  m_parent = parent;


  char_selector = new QLabel(parent);
  //char_selector->setParent(parent);
  char_selector->setStyleSheet("border-image:url(" + getImagePath("char_selector.png") + ")");
  char_selector->setAttribute(Qt::WA_TransparentForMouseEvents);
  char_selector->resize(62, 62);
  char_selector->move(x_pos - 1, y_pos - 1);

  char_selector->hide();
}

void charicon::setIcon(QString character)
{
  m_character = character;

  QString path = getCharPath(character) + "char_icon.png";

  //LEGACY SUPPORT, for ao classic filestructure
  QString legacy_path = getBasePath() + "misc/DemoThings/" + character + "_char_icon.png";

  //we also need a lowercase version for the legacy support. again because of inconsistent naming

  QString legacy_path_lower = getBasePath() + "misc/DemoThings/" + character.toLower() + "_char_icon.png";

  if (fileExists(path, true))
  {
    this->setStyleSheet("border-image:url(" + path + ")");
    this->show();
  }
  else if (fileExists(legacy_path, true))
  {
    this->setStyleSheet("border-image:url(" + legacy_path + ")");
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
  //ui->char_selector->hide();
  char_selector->hide();
  QPushButton::leaveEvent(e);
}

void charicon::enterEvent(QEvent * e)
{
  //ui->char_selector.char_selector.move(10, 10);
  //Courtroom.char_selector.show();
  char_selector->show();
  setFlat(false);
  QPushButton::enterEvent(e);
}

void charicon::released()
{
  callError("ohai");
  m_parent->hide();
}

charicon::~charicon()
{

}
