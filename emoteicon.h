#ifndef EMOTEICON_H
#define EMOTEICON_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <QLabel>

#include "error_handler.h"
#include "globals.h"
#include "config_handler.h"


class emoteicon : public QPushButton
{

  Q_OBJECT

public:
  emoteicon();
  emoteicon(int x_pos, int y_pos, QWidget *parent);
  QWidget *m_parent;

  QLabel *selected_overlay;
  bool is_selected = false;

  void setIcon(QString character, int n_emote);
  void set_selected();
  void reset();

  ~emoteicon();
};

#endif // EMOTEICON_H
