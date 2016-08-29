#include "emoteicon.h"

emoteicon::emoteicon()
{

}

emoteicon::emoteicon(int x_pos, int y_pos, QWidget *parent)
{
  this->setParent(parent);
  this->resize(40, 40);
  this->move(x_pos, y_pos);
  this->hide();

  notselected_overlay = new QLabel(this);

  if (fileExists(g_theme_path + "emote_selected.png"))
    notselected_overlay->setStyleSheet("border-image:url(" + g_theme_path + "emote_selected.png" + ")");

  notselected_overlay->setAttribute(Qt::WA_TransparentForMouseEvents);
  notselected_overlay->resize(40, 40);
  notselected_overlay->move(0, 0);

  this->hide();
}

emoteicon::~emoteicon()
{
  delete notselected_overlay;
}

void emoteicon::setIcon(QString character, int n_emote)
{
  //need upper and lowercase button because of inconsistent naming
  QString path = getCharPath(character) + "emotions/button" + QString::number(n_emote) + ".png";
  QString path_capital = getCharPath(character) + "emotions/Button" + QString::number(n_emote) + ".png";

  QString legacy_path = getCharPath(character) + "emotions/button" + QString::number(n_emote) + "_on.png";
  QString legacy_path_capital = getCharPath(character) + "emotions/Button" + QString::number(n_emote) + "_on.png";

  if (fileExists(path, true))
  {
    this->setStyleSheet("border-image:url(" + path + ")");
  }
  else if (fileExists(path_capital, true))
  {
    this->setStyleSheet("border-image:url(" + path_capital + ")");
  }

  else if (fileExists(legacy_path, true))
  {
    this->setStyleSheet("border-image:url(" + legacy_path + ")");
  }

  else if (fileExists(legacy_path_capital, true))
  {
    this->setStyleSheet("border-image:url(" + legacy_path_capital + ")");
  }

  else
  {
    this->setStyleSheet("border-image:url()");
  }

}

void emoteicon::set_selected()
{
  is_selected = true;
}

void emoteicon::reset()
{
  is_selected = false;
  this->hide();
}
