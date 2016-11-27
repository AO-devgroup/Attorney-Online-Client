#include "emotes.h"

//simply makes the ten emote widgets
void::Courtroom::construct_emotes()
{
  const int base_x_pos{10};
  const int base_y_pos{219};

  const int x_modifier{49};
  int x_mod_count{0};

  const int y_modifier{47};
  int y_mod_count{0};

  for(int n_icon{0} ; n_icon < 10 ; ++n_icon)
  {
    int x_pos = base_x_pos + (x_modifier * x_mod_count);
    int y_pos = base_y_pos + (y_modifier * y_mod_count);

    emoteicon_list.insert(n_icon, new emoteicon(x_pos, y_pos, this));

    connect (emoteicon_list.at(n_icon), SIGNAL(clicked()), emote_mapper, SLOT(map())) ;
    emote_mapper->setMapping (emoteicon_list.at(n_icon), n_icon) ;

    ++x_mod_count;

    //if char number is divisible by ten with rest 9 then the next charicon should start on a new line
    if (n_icon % 5 == 4 && n_icon != 0)
    {
      ++y_mod_count;
      x_mod_count = 0;
    }
  }

  emote_left_button = new QPushButton(this);
  emote_right_button = new QPushButton(this);

  emote_left_button->move(0, 253);
  emote_left_button->resize(20, 20);

  emote_right_button->move(236, 253);
  emote_right_button->resize(20, 20);

  connect(emote_left_button, SIGNAL(clicked()), this, SLOT(emote_left_clicked()));
  connect(emote_right_button, SIGNAL(clicked()), this, SLOT(emote_right_clicked()));

  emote_left_button->hide();
  emote_right_button->hide();

  connect(emote_mapper, SIGNAL(mapped(int)), this, SLOT(emote_choose(int)));

  for(emoteicon *i_emote : emoteicon_list)
  {
    i_emote->selected_overlay->hide();
  }
}

void Courtroom::setEmotes()
{
  QString char_ini_path = getBasePath() + "characters/" + playerChar.toLower() + "/char.ini";

  QFile char_ini(char_ini_path);
  if (!char_ini.open(QIODevice::ReadOnly))
  {
    callFatalError("failed to open " + char_ini_path + " for reading.");
    return;
  }

  QTextStream in(&char_ini);
  QStringList char_ini_list;
  QString line;
  for(int line_number{0} ; !in.atEnd() ; ++line_number)
  {
    line = in.readLine();

    char_ini_list.insert(line_number, line);
  }

  char_ini.close();

  int int_emotions_line = -1;
  int int_soundn_line = -1;
  int int_soundt_line = -1;
  int n_emotes_ini = -1;

  for(int n_line = 0 ; n_line < char_ini_list.size() ; ++n_line)
  {
    QString line = char_ini_list.at(n_line).toLower();

    if (line.startsWith("[emotions]"))
      int_emotions_line = n_line;

    if (line.startsWith("[soundn]"))
      int_soundn_line = n_line;

    if (line.startsWith("[soundt]"))
      int_soundt_line = n_line;

    if (line.startsWith("number = "))
    {
      n_emotes_ini = line.remove(0, 9).toInt();
    }
    if (line.startsWith("number= "))
    {
      n_emotes_ini = line.remove(0, 8).toInt();
    }
    if (line.startsWith("number ="))
    {
      n_emotes_ini = line.remove(0, 8).toInt();
    }
    if (line.startsWith("number="))
    {
      n_emotes_ini = line.remove(0, 7).toInt();
    }
  }

  QString err_str = "DEFAULT_EMOTE_ERROR";

  //checks that we actually found what we need
  if (int_emotions_line == -1)
  {
    err_str = "Could not find [Emotions] in " + char_ini_path;
    //callError(err_str);
    return;
  }

  if (int_soundn_line == -1)
  {
    err_str = "Could not find [SoundN] in " + char_ini_path;
    //callError(err_str);
    return;
  }

  if (int_soundt_line == -1)
  {
    err_str = "Could not find [SoundT] in " + char_ini_path;
    //callError(err_str);
    return;
  }

  if (n_emotes_ini == -1)
  {
    err_str = "Could not find emote number(number = ) in " + char_ini_path;
    //callError(err_str);
    return;
  }

  int emote_counter = 1;
  emote_list.clear();

  emote_type f_emote;

  for(int n_iteration = 1 ; n_iteration <= n_emotes_ini ; ++n_iteration)
  {

    //we need a whopping three of these because INCONSISTENCIES
    QString search_line = QString::number(emote_counter) + " = ";
    QString search_line2 = QString::number(emote_counter) + "= ";
    QString search_line3 = QString::number(emote_counter) + "=";

  //yes this for loop is nested cry me a river
  for(int n_line = int_emotions_line ; n_line < int_soundn_line ; ++n_line)
  {
    QString line = char_ini_list.at(n_line);

    if (line.startsWith(search_line))
    {
      //removes "x = " from the start of the string
      QString cropped_line = line.remove(0, 4);
      QStringList single_emote_line = cropped_line.split("#");

      //dodging those silly index out of range crashes
      if (single_emote_line.size() < 4)
      {
        QString err_str = "Misformatted emote line in file " + char_ini_path + " on line " + n_line;
        callFatalError(err_str);
        return;
      }

      f_emote.comment = single_emote_line.at(0);
      f_emote.preanim = single_emote_line.at(1);
      f_emote.anim = single_emote_line.at(2);
      f_emote.mod = single_emote_line.at(3).toInt();

      emote_list.insert(emote_counter - 1, f_emote);

      ++emote_counter;
    }

    else if (line.startsWith(search_line2))
    {
      //removes "x= " from the start of the string
      QString cropped_line = line.remove(0, 3);
      QStringList single_emote_line = cropped_line.split("#");

      //dodging those silly index out of range crashes
      if (single_emote_line.size() < 4)
      {
        QString err_str = "Misformatted emote line in file " + char_ini_path + " on line " + n_line;
        callFatalError(err_str);
        return;
      }

      f_emote.comment = single_emote_line.at(0);
      f_emote.preanim = single_emote_line.at(1);
      f_emote.anim = single_emote_line.at(2);
      f_emote.mod = single_emote_line.at(3).toInt();

      emote_list.insert(emote_counter - 1, f_emote);

      ++emote_counter;
    }

    else if (line.startsWith(search_line3))
    {
      QString cropped_line = line.remove(0, 2);
      QStringList single_emote_line = cropped_line.split("#");

      //dodging those silly index out of range crashes
      if (single_emote_line.size() < 4)
      {
        QString err_str = "Misformatted emote line in file " + char_ini_path + " on line " + n_line;
        callFatalError(err_str);
        return;
      }

      f_emote.comment = single_emote_line.at(0);
      f_emote.preanim = single_emote_line.at(1);
      f_emote.anim = single_emote_line.at(2);
      f_emote.mod = single_emote_line.at(3).toInt();

      emote_list.insert(emote_counter - 1, f_emote);

      ++emote_counter;
    }
  }

  }

  emote_counter = 1;

  for(int n_iteration = 1 ; n_iteration <= n_emotes_ini ; ++n_iteration)
  {

  for(int n_line = int_soundn_line ; n_line < int_soundt_line ; ++n_line)
  {
    //what we are doing here is finding sound effect names
    //dodging index out of range
    if (emote_counter - 1 >= emote_list.size())
      break;

    QString line = char_ini_list.at(n_line);

    QString search_line = QString::number(emote_counter) + " =";
    QString search_line2 = QString::number(emote_counter) + "=";

    if (line.startsWith(search_line))
    {
      QString f_sfx_name;
      //removes "x = " from the start of the string

      f_sfx_name = line.remove(0, search_line.length());

      emote_list[emote_counter - 1].sfx_name = f_sfx_name.trimmed();

      ++emote_counter;
    }

    else if (line.startsWith(search_line2))
    {
      QString f_sfx_name;

      f_sfx_name = line.remove(0, search_line2.length());

      emote_list[emote_counter - 1].sfx_name = f_sfx_name.trimmed();

      ++emote_counter;
    }
  }
  }

  emote_counter = 1;

  for(int n_iteration = 1 ; n_iteration <= n_emotes_ini ; ++n_iteration)
  {

  for(int n_line = int_soundt_line ; n_line < char_ini_list.size() ; ++n_line)
  {
    //what we are doing here is finding sound effect delays
    //dodging index out of range
    if (emote_counter - 1 >= emote_list.size())
      break;

    QString line = char_ini_list.at(n_line);
    QString search_line = QString::number(emote_counter) + " =";
    QString search_line2 = QString::number(emote_counter) + "=";

    if (line.startsWith(search_line))
    {
      //removes "x = " from the start of the string
      int f_sfx_delay = line.remove(0, search_line.length()).toInt();

      emote_list[emote_counter - 1].sfx_delay = f_sfx_delay;

      ++emote_counter;
    }

    else if (line.startsWith(search_line2))
    {
      int f_sfx_delay = line.remove(0, search_line2.length()).toInt();

      emote_list[emote_counter - 1].sfx_delay = f_sfx_delay;

      ++emote_counter;
    }

  }
  }

  int n_emotes = emote_list.size();
  if (n_emotes == 0)
  {
    callError("Something went horribly wrong with setting the emotes. (emote_list.size() = 0)");
    return;
  }

  if (n_emotes % 10 == 0)
    emote_pages = n_emotes / 10;

  else
  {
    emote_pages = (n_emotes / 10) + 1;
  }

  emote_current_page = 1;

  //reset here means everything unselected and hiding
  for(emoteicon *i_emote : emoteicon_list)
  {
    i_emote->reset();
  }

  QString icon_path = getBasePath() + "characters/" + playerChar + "/emotions/button1_on.png";
  QString icon_notselected_path = getBasePath() + "characters/" + playerChar + "/emotions/button";

  for (int n_icon = 1 ; n_icon <= emoteicon_list.size() ; ++n_icon)
  {
    emoteicon *i_emote = emoteicon_list.at(n_icon - 1);
    i_emote->setStyleSheet("border-image:url(" + icon_notselected_path + QString::number(n_icon) + "_off.png" + ")");
  }

  emoteicon_list.at(0)->setStyleSheet("border-image:url(" + icon_path + ")");

  //set the first emote to be selected so we avoid silly errors
  emote_selected = 0;
}

//called every time the emote page is changed
void Courtroom::setEmotePage()
{
  //first we reset(hide) everything

  for(emoteicon *i_emote : emoteicon_list)
  {
    i_emote->hide();
  }

  emote_left_button->hide();
  emote_right_button->hide();

  emotes_on_page = -1;
  int total_emotes = emote_list.size();

  if(emote_pages < 1)                        //SANITY CHECK
    callError("amount of emote pages appear to be zero or negative");

  else if(emote_pages == 1)                  //first we check if there is only one page of emotes
    emotes_on_page = total_emotes;

  else if(emote_current_page == emote_pages) //if not, then we check if we're on the last page
  {
    //it total_emotes is a multiple of ten, the page obviously has 10 emotes
    if (total_emotes % 10 == 0)
      emotes_on_page = 10;
    else
      emotes_on_page = (total_emotes % 10);
  }

  else if(emote_current_page < emote_pages)  //if not, we should be on a page that is not the last page
    emotes_on_page = 10;                     //conclusion: 10 emotes on the page

  else if(emotes_on_page == -1)
    callFatalError("emotes_on_page was not set properly (-1)");

  else
    callFatalError("Something broke with the emotes idk. blame the terrible developers."
                   "seriously, though. emotes_on_page failed to set properly. who knows why."
                   "this error should never appear ever ever");

  //anything higher than the first page must have the left arrow
  if (emote_current_page > 1)
    emote_left_button->show();

  //as long as the max amount of pages is higher than the current one, right arrow is shown
  if (emote_current_page < emote_pages)
    emote_right_button->show();

  int real_emote_modifier = (10 * (emote_current_page - 1));

  for(int n_local_emote = 0 ; n_local_emote < emotes_on_page ; ++n_local_emote)
  {
    int n_real_emote = n_local_emote + real_emote_modifier;

    emoteicon_list.at(n_local_emote)->setIcon(playerChar, n_real_emote + 1);
    emoteicon_list.at(n_local_emote)->show();

    if(emote_selected == n_real_emote)
    {
      //emoteicon_list.at(n_local_emote)->selected_overlay->show();
      QString icon_path = getBasePath() + "characters/" + playerChar.toLower() + "/emotions/button" + QString::number(n_real_emote + 1) + "_on.png";

      emoteicon_list.at(n_local_emote)->setStyleSheet("border-image:url(" + icon_path + ")");
    }
    else
    {
      //emoteicon_list.at(n_local_emote)->selected_overlay->hide();
      QString icon_path = getBasePath() + "characters/" + playerChar.toLower() + "/emotions/button" + QString::number(n_real_emote + 1) + "_off.png";

      emoteicon_list.at(n_local_emote)->setStyleSheet("border-image:url(" + icon_path + ")");
    }
  }
}

void Courtroom::emote_choose(int local_emote_number)
{
  int real_emote_modifier = (10 * (emote_current_page - 1));
  int n_real_emote = local_emote_number + real_emote_modifier;

  ui->chatLine->setFocus();

  /*
  for(emoteicon *i_emote : emoteicon_list)
  {
    i_emote->selected_overlay->hide();
  }
  */

  //emoteicon_list.at(local_emote_number)->selected_overlay->show();

  QString icon_path = getBasePath() + "characters/" + playerChar.toLower() + "/emotions/button" + QString::number(n_real_emote + 1) + "_on.png";
  QString icon_notselected_path = getBasePath() + "characters/" + playerChar.toLower() + "/emotions/button";

  for (int n_icon = 1 ; n_icon <= emoteicon_list.size() ; ++n_icon)
  {
    int f_real_emote = n_icon + real_emote_modifier;
    emoteicon *i_emote = emoteicon_list.at(n_icon - 1);
    i_emote->setStyleSheet("border-image:url(\"" + icon_notselected_path + QString::number(f_real_emote) + "_off.png" + "\")");
  }

  emoteicon_list.at(local_emote_number)->setStyleSheet("border-image:url(\"" + icon_path + "\")");
  emote_selected = n_real_emote;

  int pre_state = emote_list.at(n_real_emote).mod;

  //intentional fallthrough here
  switch (pre_state)
  {
  case 1:
    ;
  case 3:
    ;
  case 4:
    ui->prebox->setChecked(true);
    break;
  default:
    ui->prebox->setChecked(false);

  }
}
