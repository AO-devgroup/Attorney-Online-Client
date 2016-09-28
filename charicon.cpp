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

  m_parent = parent;

  taken_overlay = new QLabel(parent);

  taken_overlay->setStyleSheet("border-image:url(" + get_image_path("char_taken.png") + ")");

  taken_overlay->setAttribute(Qt::WA_TransparentForMouseEvents);
  taken_overlay->resize(60, 60);
  taken_overlay->move(x_pos, y_pos);
  taken_overlay->hide();

  password_overlay = new QLabel(parent);

  password_overlay->setStyleSheet("border-image:url(" + get_image_path("char_passworded.png") + ")");

  password_overlay->setAttribute(Qt::WA_TransparentForMouseEvents);
  password_overlay->resize(60, 60);
  password_overlay->move(x_pos, y_pos);
  password_overlay->hide();

  // i dont even know if this code is used
  char_selector = new QLabel(parent);
  char_selector->setStyleSheet("border-image:url(" + get_image_path("char_selector.png") + ")");
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
    QFile::copy(legacy_path, path);
  }
  else if (fileExists(legacy_path_lower, true))
  {
    this->setStyleSheet("border-image:url(" + legacy_path_lower + ")");
    this->show();
    QFile::copy(legacy_path_lower, path);
  }
  //if the char icon could not be found we add a neat text label to help the user :)
  else
  {
    this->setText(character);
    this->show();
  }

}

void charicon::set_taken()
{
  taken_overlay->show();
}

void charicon::set_passworded()
{
  password_overlay->show();
}

void charicon::reset()
{
  this->setStyleSheet("border-image:url()");
  this->setText("");
  taken_overlay->hide();
  password_overlay->hide();
  this->hide();
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
  char_selector->raise();
  char_selector->show();
  setFlat(false);
  QPushButton::enterEvent(e);
}

charicon::~charicon()
{
  delete taken_overlay;
  delete char_selector;
}
