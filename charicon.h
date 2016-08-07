#ifndef CHARICON_H
#define CHARICON_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <QLabel>

#include "ui_courtroom.h"

#include "error_handler.h"
#include "character_handler.h"


class charicon : public QPushButton
{

  Q_OBJECT

public:
  charicon();
  charicon(int x_pos, int y_pos, QWidget *parent);
  QString m_character;
  QWidget *m_parent;
  QLabel *char_selector;
  bool m_is_selected = false;
  void setIcon(QString character);
  ~charicon();

//private slots:
  //void handleClick(int char_number);

protected:
  void enterEvent(QEvent *e);
  void leaveEvent(QEvent *e);
  void released();

//signals:
  //void charClicked(int char_number);

//private slots:
  //void handleButton();
};

class chartaken : public QLabel
{
public:
  chartaken();
  chartaken(int x_pos, int y_pos, QWidget *parent);
};

#endif // CHARICON_H
