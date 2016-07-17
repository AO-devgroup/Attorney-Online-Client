#ifndef CHARICON_H
#define CHARICON_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <QLabel>

#include "ui_courtroom.h"

#include "error_handler.h"
#include "character_handler.h"
#include "courtroom.h"


class charicon : public QPushButton
{

public:
  charicon(int x_pos, int y_pos, QString character, QWidget *parent);
  ~charicon();
  QString m_character;
  bool m_is_selected = false;

protected:
  void enterEvent(QEvent *e);
  void leaveEvent(QEvent *e);
  void clicked();

//private:
//  QLabel selector;
};

#endif // CHARICON_H
