#include "charselect.h"

void Courtroom::construct_charselect()
{
  //setting up the grid and positions
  const int base_x_pos{25};
  const int base_y_pos{36};

  const int x_modifier{67};
  int x_mod_count{0};

  const int y_modifier{67};
  int y_mod_count{0};

  //QSignalMapper* signalMapper = new QSignalMapper (this) ;


  //in this loop we simply make 90 widgets and connect them, they start off empty
  for(int n_icon{0} ; n_icon < 90 ; ++n_icon)
  {
    int x_pos = base_x_pos + (x_modifier * x_mod_count);
    int y_pos = base_y_pos + (y_modifier * y_mod_count);

    charicon_list.insert(n_icon, new charicon(x_pos, y_pos, ui->charselect));

    connect (charicon_list.at(n_icon), SIGNAL(clicked()), mapper, SLOT(map())) ;
    mapper->setMapping (charicon_list.at(n_icon), n_icon) ;

    ++x_mod_count;

    //if char number is divisible by ten with rest 9 then the next charicon should start on a new line
    if (n_icon % 10 == 9 && n_icon != 0)
    {
      ++y_mod_count;
      x_mod_count = 0;
    }
  }

  connect (mapper, SIGNAL(mapped(int)), this, SLOT(charChoose(int))) ;

  QString d_path = getBasePath() + "themes/default/";

  QString char_select_path = g_theme_path + "charselect_background.png";
  QString d_char_select_path = d_path + "charselect_background.png";

  QString left_arrow_path = g_theme_path + "arrow_left.png";
  QString d_left_arrow_path = d_path + "arrow_left.png";

  QString right_arrow_path = g_theme_path + "arrow_right.png";
  QString d_right_arrow_path = d_path + "arrow_right.png";

  if (fileExists(char_select_path, true))
    ui->charselect->setPixmap(QPixmap(char_select_path));
  else if (fileExists(d_char_select_path))
    ui->charselect->setPixmap(QPixmap(d_char_select_path));

  if (fileExists(left_arrow_path, true))
    ui->charselect_left->setStyleSheet("border-image:url(" + left_arrow_path + ")");
  else if (fileExists(d_left_arrow_path))
    ui->charselect_left->setStyleSheet("border-image:url(" + d_left_arrow_path + ")");

  if (fileExists(right_arrow_path, true))
    ui->charselect_right->setStyleSheet("border-image:url(" + right_arrow_path + ")");
  else if (fileExists(d_right_arrow_path))
    ui->charselect_right->setStyleSheet("border-image:url(" + d_right_arrow_path + ")");

  for (charicon *f_icon : charicon_list){
    f_icon->hide();
  }
}

//called on character_list_received from network handler
void Courtroom::set_character_list(QVector<char_type> &p_char_list)
{
  character_list = p_char_list;
  char_list_set = true;

  mutelist.clear();
  ui->mutelist->clear();

  for (int n_char = 0 ; n_char < character_list.size() ; ++n_char)
  {
    mutelist.insert(n_char, false);

    ui->mutelist->addItem(character_list.at(n_char).name);
  }

  if (character_list.size() % 90 == 0)
    char_select_pages = character_list.size() / 90;
  else
    char_select_pages = (character_list.size() / 90) + 1;

  char_select_current_page = 1;

  if (taken_list_set && done_received)
  {
    setCharSelectPage();
    enter_courtroom();
    show();
  }
}

void Courtroom::set_taken_list(QVector<int> &p_taken_list)
{
  taken_list = p_taken_list;
  taken_list_set = true;

  if (char_list_set && done_received)
  {
    if (character_list.size() != taken_list.size())
    {
      callError("CRITICAL FISSION MAILURE: taken_list.size did not match char_list.size");
      return;
    }
    setCharSelectPage();
    enter_courtroom();
    show();
  }
}

//obsolete
/*
void Courtroom::setCharSelect()
{


  char_select_current_page = 1;

  setCharSelectPage();


}
*/

void Courtroom::setCharSelectPage()
{
  int char_list_size = character_list.size();


  //start by hiding left and right arrows because were
  //not certain at this point if they should appear or not
  ui->charselect_left->hide();
  ui->charselect_right->hide();

  ui->charError->hide();

  //we reset all charicons first(this includes hiding)
  for(charicon *f_charicon : charicon_list)
  {
    f_charicon->reset();
  }

  int chars_on_page = -1;

  //SANITY CHECK
  if(char_select_pages < 1)
    callError("amount of character pages appear to be zero or negative");

  //check if there is only one page of characters
  else if(char_select_pages == 1)
    chars_on_page = char_list_size;

  //check if we are on the first page
  else if(char_select_current_page == 1)
  {
    if(char_select_pages == 1)
      chars_on_page = char_list_size;
    else if(char_select_pages > 1)
      chars_on_page = 90;
    else
      callError("char_select_current_page == 1 returned true but somehow char_select_pages was set wrong");
  }

  //check if we are on the last page
  else if(char_select_current_page == char_select_pages)
  {
    //then we check if the amount of chars we have is a multiple of 90
    if (char_list_size % 90 == 0)
      chars_on_page = 90;
    else
      chars_on_page = (char_list_size % 90);
  }

  //if none of the above are true, we have to be somewhere in the middle, which means 90 chars
  else if(char_select_current_page < char_select_pages && char_select_current_page > 1)
    chars_on_page = 90;

  else if(chars_on_page == -1)
    callFatalError("emotes_on_page was not set properly (-1)");

  else
    callFatalError("Something broke with the charselect idk. blame the terrible developers."
                   "seriously, though. chars_on_page failed to set properly. who knows why."
                   "this error should never appear ever ever");


  //used to detemine if its char # 1, 91, 181 etc.
  int real_char_modifier = (90 * (char_select_current_page - 1));

  for(int local_char_number{0} ; local_char_number < chars_on_page ; ++local_char_number)
  {
    int real_char_number = local_char_number + real_char_modifier;

    charicon *f_charicon = charicon_list.at(local_char_number);
    char_type f_char = character_list.at(real_char_number);

    f_charicon->setIcon(f_char.name);

    int f_mod = taken_list.at(real_char_number);

    switch (f_mod)
    {
    case 0:
      break;
    case 1:
      f_charicon->set_taken();
      break;
    case 2:
      f_charicon->set_passworded();
      break;
    case 3:
      f_charicon->set_taken();
      f_charicon->set_passworded();
      break;
    default:
      callError("SOMETHING BROKE. f_mod in function setCharSelectPage was not in 0-3, but rather " + f_mod);

    }

    f_charicon->show();
  }

  //anything higher than the first page must have the left arrow
  if (char_select_current_page > 1)
    ui->charselect_left->show();

  //as long as the current page is less than max amount of pages, right arrow is shown
  if (char_select_current_page < char_select_pages)
    ui->charselect_right->show();
}


void Courtroom::charChoose(int local_charnumber)
{
  //we first need to figure out which character we have based on page number and
  //icon number

  int real_char_number;
  QString real_char;

  real_char_number = local_charnumber + (90 * (char_select_current_page - 1));
  real_char = character_list.at(real_char_number).name;

  QString f_password = ui->charpass->text();

  m_cid = real_char_number;

  if (!fileExists(getBasePath() + "characters/" + real_char + "/char.ini", false))
  {
    return;
  }

  character_requested(real_char_number, f_password);
}
