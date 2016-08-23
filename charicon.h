#ifndef CHARICON_H
#define CHARICON_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <QLabel>

#include "ui_courtroom.h"

#include "error_handler.h"


class charicon : public QPushButton
{

  Q_OBJECT

public:
  charicon();
  charicon(int x_pos, int y_pos, QWidget *parent);
  QString m_character;
  QWidget *m_parent;
  QLabel *char_selector;
  QLabel *taken_overlay;
  QLabel *password_overlay;
  bool m_is_selected = false;

  void setIcon(QString character);
  void set_taken();
  void set_passworded();
  void reset();

  ~charicon();

protected:
  void enterEvent(QEvent *e);
  void leaveEvent(QEvent *e);

};


#endif // CHARICON_H
