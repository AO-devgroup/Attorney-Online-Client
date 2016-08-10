#include "courtroom.h"


Courtroom::Courtroom(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Courtroom)
{
  ui->setupUi(this);
  this->setWindowTitle("Attorney Online");
}

void Courtroom::setTheme()
{
  LoadConfig();

  QString background_path = getImagePath("courtroombackground.png");
  QString holdit_path = getImagePath("holdit_disabled.png");
  QString objection_path = getImagePath("objection_disabled.png");
  QString takethat_path = getImagePath("takethat_disabled.png");
  QString present_path = getImagePath("present_disabled.png");
  QString left_arrow_path = getImagePath("arrow_left.png");
  QString right_arrow_path = getImagePath("arrow_right.png");

  if (fileExists(background_path))
    ui->background->setPixmap(QPixmap(background_path));

  if (fileExists(holdit_path))
    ui->holdit->setStyleSheet("border-image:url(" + holdit_path + ")");

  if (fileExists(objection_path))
    ui->objection->setStyleSheet("border-image:url(" + objection_path + ")");

  if (fileExists(takethat_path))
    ui->takethat->setStyleSheet("border-image:url(" + takethat_path + ")");

  if (fileExists(present_path))
    ui->present->setStyleSheet("border-image:url(" + present_path + ")");

  if (fileExists(left_arrow_path))
    ui->emote_left->setStyleSheet("border-image:url(" + left_arrow_path + ")");

  if (fileExists(right_arrow_path))
    ui->emote_right->setStyleSheet("border-image:url(" + right_arrow_path + ")");

}

void Courtroom::setChar()
{
//  LoadCharIni(playerChar); //This isn't needed anymore since we'll use QSettings from now on.

  setEmotes();

  emote_pressed = 1;

  if (emote_number == -1)
    callFatalError("failed to get emote_number (-1)");

  if ((emote_number % 10) == 0)             //we check if the amount of emotes is divisible by ten
    emote_pages = (emote_number / 10);
  else
    emote_pages = ((emote_number / 10) + 1);

  emote_current_page = 1;

  setEmotePage();

  ui->emote1->setStyleSheet("border-image:url(" + getEmoteIconPath(1) + "_on.png" + ")");

  ui->chatLine->show();
  ui->objection->show();
  ui->holdit->show();
  ui->takethat->show();
  ui->present->show();
}

void Courtroom::setCharSelect()
{
  char_select_list = getCharSelectList();

  char_amount = char_select_list.size() - 1;  //we need to remove the "null" char

  setTakenChars();

  //we need to fill in indexes 0 for later logic to flow
  charicon_list.insert(0, nullptr);
  char_taken_list.insert(0, nullptr);

  //you raise me uup
  //srs, tho. brings the ui in front of the rest of the courtroom
  ui->charselect->raise();
  ui->charselect_left->raise();
  ui->charselect_right->raise();
  ui->spectator->raise();

  //so when we show() and hide() charselect, children follow suit
  ui->charselect_left->setParent(ui->charselect);
  ui->charselect_right->setParent(ui->charselect);
  ui->spectator->setParent(ui->charselect);

  //setting up the grid and positions
  const int base_x_pos{25};
  const int base_y_pos{36};

  const int x_modifier{67};
  int x_mod_count{0};

  const int y_modifier{67};
  int y_mod_count{0};

  QSignalMapper* signalMapper = new QSignalMapper (this) ;

  for(int n_icon{1} ; n_icon <= 90 ; ++n_icon)
  {
    int x_pos = base_x_pos + (x_modifier * x_mod_count);
    int y_pos = base_y_pos + (y_modifier * y_mod_count);


    charicon_list.insert(n_icon, new charicon(x_pos, y_pos, ui->charselect));
    char_taken_list.insert(n_icon, new chartaken(x_pos, y_pos, ui->charselect));

    char_taken_list.at(n_icon)->hide();

    connect (charicon_list.at(n_icon), SIGNAL(clicked()), signalMapper, SLOT(map())) ;
    signalMapper -> setMapping (charicon_list.at(n_icon), n_icon) ;

    //connect(charicon_list.at(n_icon), SIGNAL (charClicked()), this, SLOT (handleCharicon()));
    //charicon_list.at(n_icon)->hide();

    ++x_mod_count;

    //if char number is divisible by ten then the next charicon should start on a new line
    if (n_icon % 10 == 0)
    {
      ++y_mod_count;
      x_mod_count = 0;
    }
  }

  connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(charChoose(int))) ;

  //delete signalMapper;

  QString left_arrow_path = getImagePath("arrow_left.png");
  QString right_arrow_path = getImagePath("arrow_right.png");

  //setting images on arrow buttons
  if (fileExists(left_arrow_path))
    ui->charselect_left->setStyleSheet("border-image:url(" + left_arrow_path + ")");

  if (fileExists(right_arrow_path))
    ui->charselect_right->setStyleSheet("border-image:url(" + right_arrow_path + ")");

  //hiding them to begin with
  ui->charselect_left->hide();
  ui->charselect_right->hide();

  //SANITY CHECK
  if (char_amount <= 0)
    callFatalError("amount of character appear to be equal or less than zero");;

  if (char_amount % 90 == 0)
    char_select_pages = char_amount / 90;
  else
    char_select_pages = (char_amount / 90) + 1;

  QString char_select_path = getImagePath("charselect_background.png");
  //QString char_selector_path = getImagePath("char_selector.png");

  if (fileExists(char_select_path))
    ui->charselect->setPixmap(QPixmap(char_select_path));
/*
  if (fileExists(char_selector_path))
  {
    char_selector.setParent(ui->charselect);
    char_selector.setPixmap(char_selector_path);
    char_selector.hide();
  }
*/

  char_select_current_page = 1;

  setCharSelectPage();
}

void Courtroom::setCharSelectPage()
{
  //start by hiding left and right arrows because were
  //not certain at this point if they should appear or not
  ui->charselect_left->hide();
  ui->charselect_right->hide();

  //we make sure all the char icons start hidden as well
  for(int n_icon{1} ; n_icon <= 90 ; ++n_icon)
  {
    charicon_list.at(n_icon)->setStyleSheet("border-image:url()");
    charicon_list.at(n_icon)->setText("");
    charicon_list.at(n_icon)->hide();
  }

  int chars_on_page = -1;

  //SANITY CHECK
  if(char_select_pages < 1)
    callError("amount of emote pages appear to be zero or negative");

  //check if there is only one page of characters
  else if(char_select_pages == 1)
    chars_on_page = char_amount;

  //check if we are on the first page
  else if(char_select_current_page == 1)
  {
    if(char_select_pages == 1)
      chars_on_page = char_amount;
    else if(char_select_pages > 1)
      chars_on_page = 90;
    else
      callError("char_select_current_page == 1 returned true but somehow char_select_pages was set wrong");
  }

  //check if we are on the last page
  else if(char_select_current_page == char_select_pages)
  {
    //then we check if the amount of chars we have is a multiple of 90
    if (char_amount % 90 == 0)
      chars_on_page = 90;
    else
      chars_on_page = (char_amount % 90);
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



  int real_char_modifier = (90 * (char_select_current_page - 1));

  for(int local_char_number{1} ; local_char_number <= chars_on_page ; ++local_char_number)
  {
    int real_char_number = local_char_number + real_char_modifier;

    charicon_list.at(local_char_number)->setIcon(char_select_list[real_char_number]);
    charicon_list.at(local_char_number)->show();

    if (chars_taken.at(real_char_number) == -1)
      char_taken_list.at(local_char_number)->show();
  }

  //anything higher than the first page must have the left arrow
  if (char_select_current_page > 1)
    ui->charselect_left->show();

  //as long as the current page is less than max amount of pages, right arrow is shown
  if (char_select_current_page < char_select_pages)
    ui->charselect_right->show();

  ui->spectator->show();

}

void Courtroom::handleCharicon(QString character)
{
  callError(character);
}

void Courtroom::charChoose(int local_charnumber)
{
  //we first need to figure out which character we have based on page number and
  //icon number

  int real_char_number;
  QString real_char;

  real_char_number = local_charnumber + (90 * (char_select_current_page - 1));
  real_char = char_select_list.at(real_char_number);

  //T0D0
  //hello mister server, can we has real_char pls?
  //if (serversaysyes)
  playerChar = real_char;
  setTheme();
  setChar();



  ui->charselect->hide();

  //else
  //ui->errorlabel->setText("Character is already taken.");
}

void Courtroom::setEmotes()
{
//  bool found_emotions = false;
//  QString line; //I don't think we'll need those things, keeping till we agreed on it
  QSettings* ini_charini = new QSettings(getCharPath(playerChar) + "char.ini", QSettings::IniFormat);

  emote_number = -1;

  ini_charini->beginGroup("Emotions"); //reach under the [Emotions] group
  if (ini_charini->contains("number")) //we can't verify the group exists in QSettings, but we can verify a key exists within it, so we check if "number" exists inside "[Emotions]"
  {
    emote_number = ini_charini->value("number", 1).toInt();
  }
  else
  {
      //do something
  }

  if (emote_number < 1)  //the following is an equivalent to the code you made, no new features yet.
  {
      callFatalError("Number of emotes appear to be zero or negative");   //Avoid fatal errors, we want to handle stuff behind the scene without troubling the user, left it for now
      emote_number = -1;
  }
      QVector<emote_type>  emote_list(QVector<emote_type>(0));

      if (!(emote_number == -1))
      {
          for (int i = 1; i <= emote_number; i++)
          {
//

              emote_type emote_struct;
              QString emote_uncut = ini_charini->value(QString::number(i), "Dankmemes#Dankmemes#Dankmemes#0#").toString(); //"dankmemes" ensure empty lines won't cause fatal errors
              QStringList emote_cut = emote_uncut.split("#");

              emote_struct.comment=emote_cut[0]; //adding all the emote "parts" in foo
              emote_struct.anim=emote_cut[1];
              emote_struct.preanim=emote_cut[2];
              emote_struct.mod=(emote_cut[3]).toInt();

              emote_list.push_back(emote_struct);


              qDebug() << "emote_list:" << emote_list.last().comment;
              qDebug() << "emote_list:" << emote_list.last().anim;
              qDebug() << "emote_list:" << emote_list.last().preanim;
              qDebug() << "emote_list:" << emote_list.last().mod;
              qDebug() << "__________" << "_______________";
          }
      }



//this is a really long comment isn't it :( BTW the closing '}' is under the comment-out

//  for(int line_number{0} ; line_number < g_char_ini.size() ; ++line_number)
//  {
//    line = g_char_ini.at(line_number);

//    //we are satisified if the line starts with target string
//    //in case someone adds a space and wonders why things break
//    if (line.startsWith("[Emotions]"))
//      found_emotions = true;

//    if (line.startsWith("number = ") && found_emotions)
//    {
//      //removes "number = " from the start of the string
//      QString newline = line.remove(0, 9);

//      //SANITY CHECK
//      if (newline.toInt() < 1)
//        callFatalError("number of emotes appear to be zero or negative");

//      emote_number = newline.toInt();
//    }

//    if (!(emote_number == -1) && line.startsWith("1 = "))
//    {

//      for(int emote_n{1} ; emote_n <= emote_number ; ++emote_n)
//      {
//        int current_line_n = line_number + emote_n - 1;
//        QString current_line = g_char_ini[current_line_n];
//        QStringList line_list = current_line.split("#");

//        emote_list.insert(emote_n, line_list[2]);
//      }
//      break;
//    }


//    //in the unlikely event that we reach EOF
//    if (line_number == (g_char_ini.size() - 1))
//    {
//      callError("could not find [Emotions] in char.ini");
//    }
//  }
}

//called every time the emote page is changed

void Courtroom::setEmotePage()
{
  //first we hide everything

  ui->emote10->hide();
  ui->emote9->hide();
  ui->emote8->hide();
  ui->emote7->hide();
  ui->emote6->hide();
  ui->emote5->hide();
  ui->emote4->hide();
  ui->emote3->hide();
  ui->emote2->hide();
  ui->emote1->hide();

  ui->emote_left->hide();
  ui->emote_right->hide();

  int emotes_on_page = -1;

  if(emote_pages < 1)                        //SANITY CHECK
    callError("amount of emote pages appear to be zero or negative");

  else if(emote_pages == 1)                  //first we check if there is only one page of emotes
    emotes_on_page = emote_number;

  else if(emote_current_page == emote_pages) //if not, then we check if we're on the last page
    emotes_on_page = (emote_number % 10);

  else if(emote_current_page < emote_pages)  //if not, we should be on a page that is not the last page
    emotes_on_page = 10;                     //conclusion: 10 emotes on the page

  else if(emotes_on_page == -1)
    callFatalError("emotes_on_page was not set properly (-1)");

  else
    callFatalError("Something broke with the emotes idk. blame the terrible developers."
                   "seriously, though. emotes_on_page failed to set properly. who knows why."
                   "this error should never appear ever ever");

  //here we check if the left and right arrows need to appear

  //anything higher than the first page must have the left arrow
  if (emote_current_page > 1)
    ui->emote_left->show();

  //as long as the max amount of pages is higher than the current one, right arrow is shown
  if (emote_current_page < emote_pages)
    ui->emote_right->show();


  /////////////////////////////////////////////////////////////////////////////////////////
  // !!!!!!INTENTIONAL FALLTHROUGH!!!!!!!!!!
  // the way this works is that if there are ten emotes on the page, all emotes will be set
  // if 9, then everything below case 9 will be executed etc.
  // remember that all emotes are hidden earlier ^
  // if a case is matched, the rest of the case checks will be IGNORED
  // that is how a switch fallthrough works, you're welcome
  /////////////////////////////////////////////////////////////////////////////////////////

  QString path;

  switch(emotes_on_page)
  {
    case 10:
      path = getEmoteIconPath(10) + "_off.png";
      if (fileExists(path))
      {
        ui->emote10->setStyleSheet("border-image:url(" + path + ")");
        ui->emote10->show();
      }

    case 9:
      path = getEmoteIconPath(9) + "_off.png";
      if (fileExists(path))
      {
        ui->emote9->setStyleSheet("border-image:url(" + path + ")");
        ui->emote9->show();
      }

    case 8:
      path = getEmoteIconPath(8) + "_off.png";
      if (fileExists(path))
      {
        ui->emote8->setStyleSheet("border-image:url(" + path + ")");
        ui->emote8->show();
      }

    case 7:
      path = getEmoteIconPath(7) + "_off.png";
      if (fileExists(path))
      {
        ui->emote7->setStyleSheet("border-image:url(" + path + ")");
        ui->emote7->show();
      }

    case 6:
      path = getEmoteIconPath(6) + "_off.png";
      if (fileExists(path))
      {
        ui->emote6->setStyleSheet("border-image:url(" + path + ")");
        ui->emote6->show();
      }

    case 5:
      path = getEmoteIconPath(5) + "_off.png";
      if (fileExists(path))
      {
        ui->emote5->setStyleSheet("border-image:url(" + path + ")");
        ui->emote5->show();
      }

    case 4:
      path = getEmoteIconPath(4) + "_off.png";
      if (fileExists(path))
      {
        ui->emote4->setStyleSheet("border-image:url(" + path + ")");
        ui->emote4->show();
      }

    case 3:
      path = getEmoteIconPath(3) + "_off.png";
      if (fileExists(path))
      {
        ui->emote3->setStyleSheet("border-image:url(" + path + ")");
        ui->emote3->show();
      }

    case 2:
      path = getEmoteIconPath(2) + "_off.png";
      if (fileExists(path))
      {
        ui->emote2->setStyleSheet("border-image:url(" + path + ")");
        ui->emote2->show();
      }

    case 1:
      path = getEmoteIconPath(1) + "_off.png";
      if (fileExists(path))
      {
        ui->emote1->setStyleSheet("border-image:url(" + path + ")");
        ui->emote1->show();
      }
  }

}

//this is some topkek bs code right here but i couldnt find a better way to do it

void Courtroom::setAllEmotesOff()
{
  QString path;

  path = getEmoteIconPath(1) + "_off.png";
  ui->emote1->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(2) + "_off.png";
  ui->emote2->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(3) + "_off.png";
  ui->emote3->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(4) + "_off.png";
  ui->emote4->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(5) + "_off.png";
  ui->emote5->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(6) + "_off.png";
  ui->emote6->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(7) + "_off.png";
  ui->emote7->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(8) + "_off.png";
  ui->emote8->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(9) + "_off.png";
  ui->emote9->setStyleSheet("border-image:url(" + path + ")");

  path = getEmoteIconPath(10) + "_off.png";
  ui->emote10->setStyleSheet("border-image:url(" + path + ")");

}

//i forgot how but this works somehow
int Courtroom::getPressedEmote()
{
  return (emote_pressed + (10 * (emote_current_page - 1)));
}

QString Courtroom::getEmoteIconPath(int emotenumber)
{
  QString str_emotenumber = QString::number(emotenumber + (10 * (emote_current_page - 1)));

  //we need to check both uppercase and lowercase B's because the files are inconsistently named

  QString smallb = getCharPath(playerChar) + "emotions/button" + str_emotenumber;
  QString bigb = getCharPath(playerChar) + "emotions/Button" + str_emotenumber;

  //true as param makes the check quiet and does not throw an error if it fails
  //we also need to check both on and off for reasons
  if (fileExists(smallb + "_off.png", true) && fileExists(smallb + "_on.png", true))
    return smallb;

  else if (fileExists(bigb + "_off.png", true) && fileExists(bigb + "_on.png", true))
    return bigb;

  //at this point, we know the file doesnt exist, but we return this and the caller handles the error
  else
    return smallb;
}

Courtroom::~Courtroom()
{
  delete ui;
}

void Courtroom::on_holdit_clicked()
{
  QString holdit_disabled_path = getImagePath("holdit_disabled.png");
  QString holdit_path = getImagePath("holdit.png");
  QString objection_path = getImagePath("objection_disabled.png");
  QString takethat_path = getImagePath("takethat_disabled.png");


  //if holdit is already enabled
  if (objection_state == 1)
  {
    objection_state = 0;
    if (fileExists(holdit_disabled_path))
      ui->holdit->setStyleSheet("border-image:url(" + holdit_disabled_path + ")");
  }
  else
  {
    objection_state = 1;
    if (fileExists(holdit_path))
      ui->holdit->setStyleSheet("border-image:url(" + holdit_path + ")");

    if (fileExists(objection_path))
      ui->objection->setStyleSheet("border-image:url(" + objection_path + ")");

    if (fileExists(takethat_path))
      ui->takethat->setStyleSheet("border-image:url(" + takethat_path + ")");
  }
}

void Courtroom::on_objection_clicked()
{
  QString objection_disabled_path = getImagePath("objection_disabled.png");
  QString objection_path = getImagePath("objection.png");
  QString holdit_path = getImagePath("holdit_disabled.png");
  QString takethat_path = getImagePath("takethat_disabled.png");


  //if objection is already enabled
  if (objection_state == 2)
  {
    objection_state = 0;
    if (fileExists(objection_disabled_path))
      ui->objection->setStyleSheet("border-image:url(" + objection_disabled_path + ")");
  }
  else
  {
    objection_state = 2;
    if (fileExists(objection_path))
      ui->objection->setStyleSheet("border-image:url(" + objection_path + ")");

    if (fileExists(holdit_path))
      ui->holdit->setStyleSheet("border-image:url(" + holdit_path + ")");

    if (fileExists(takethat_path))
      ui->takethat->setStyleSheet("border-image:url(" + takethat_path + ")");
  }
}

void Courtroom::on_takethat_clicked()
{
  QString takethat_disabled_path = getImagePath("takethat_disabled.png");
  QString takethat_path = getImagePath("takethat.png");
  QString holdit_path = getImagePath("holdit_disabled.png");
  QString objection_path = getImagePath("objection_disabled.png");


  //if takethat is already enabled
  if (objection_state == 3)
  {
    objection_state = 0;

    if (fileExists(takethat_disabled_path))
      ui->takethat->setStyleSheet("border-image:url(" + takethat_disabled_path + ")");
  }
  else
  {
    objection_state = 3;

    if (fileExists(takethat_path))
      ui->takethat->setStyleSheet("border-image:url(" + takethat_path + ")");

    if (fileExists(objection_path))
      ui->objection->setStyleSheet("border-image:url(" + objection_path + ")");

    if (fileExists(holdit_path))
      ui->holdit->setStyleSheet("border-image:url(" + holdit_path + ")");
  }
}

void Courtroom::on_present_clicked()
{
  QString present_on = getImagePath("present.png");
  QString present_off = getImagePath("present_disabled.png");

  if (present_evidence)
  {
    ui->present->setStyleSheet("border-image:url(" + present_off + ")");
    present_evidence = false;
  }

  else
  {
    ui->present->setStyleSheet("border-image:url(" + present_on + ")");
    present_evidence = true;
  }
}

void Courtroom::on_chatLine_returnPressed()
{
  QString chatMessage = ui->chatLine->text();
  ui->plainTextEdit->appendPlainText(chatMessage);
  ui->chatLine->clear();

  ui->playingbackground->setPixmap(getBasePath() + "background/gs4/defenseempty.png");
  ui->desk->setPixmap(getBasePath() + "background/gs4/bancodefensa.png");
  ui->chatbubble->setPixmap(getImagePath("chat.png"));

  QMovie *movie = new QMovie(getCharGifPath(playerChar, "(b)" + emote_list[getPressedEmote()].anim + ".gif"));
  ui->playingarea->setMovie(movie);

  movie->start();
}

void Courtroom::on_emote1_clicked()
{
  ui->chatLine->setFocus();

  int n = 1;

  setAllEmotesOff();

  ui->emote1->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote2_clicked()
{
  ui->chatLine->setFocus();

  int n = 2;

  setAllEmotesOff();

  ui->emote2->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote3_clicked()
{
  ui->chatLine->setFocus();

  int n = 3;

  setAllEmotesOff();

  ui->emote3->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote4_clicked()
{
  ui->chatLine->setFocus();

  int n = 4;

  setAllEmotesOff();

  ui->emote4->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote5_clicked()
{
  ui->chatLine->setFocus();

  int n = 5;

  setAllEmotesOff();

  ui->emote5->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote6_clicked()
{
  ui->chatLine->setFocus();

  int n = 6;

  setAllEmotesOff();

  ui->emote6->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote7_clicked()
{
  ui->chatLine->setFocus();

  int n = 7;

  setAllEmotesOff();

  ui->emote7->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote8_clicked()
{
  ui->chatLine->setFocus();

  int n = 8;

  setAllEmotesOff();

  ui->emote8->setStyleSheet("border-image:url(" +
                            getEmoteIconPath(n) +
                            "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote9_clicked()
{
  ui->chatLine->setFocus();

  int n = 9;

  setAllEmotesOff();

  ui->emote9->setStyleSheet("border-image:url(" + getEmoteIconPath(n) + "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote10_clicked()
{
  ui->chatLine->setFocus();

  int n = 10;

  setAllEmotesOff();

  ui->emote10->setStyleSheet("border-image:url(" + getEmoteIconPath(n) + "_on.png" + ")");
  emote_pressed = n;
}

void Courtroom::on_emote_left_clicked()
{
  --emote_current_page;
  setEmotePage();
}

void Courtroom::on_emote_right_clicked()
{
  ++emote_current_page;
  setEmotePage();
}


void Courtroom::on_spectator_clicked()
{
    ui->objection->hide();
    ui->holdit->hide();
    ui->takethat->hide();
    ui->present->hide();

    ui->emote10->hide();
    ui->emote9->hide();
    ui->emote8->hide();
    ui->emote7->hide();
    ui->emote6->hide();
    ui->emote5->hide();
    ui->emote4->hide();
    ui->emote3->hide();
    ui->emote2->hide();
    ui->emote1->hide();

    ui->emote_left->hide();
    ui->emote_right->hide();

    ui->chatLine->hide();

    ui->charselect->hide();
}

void Courtroom::on_charselect_left_clicked()
{
  --char_select_current_page;
  setCharSelectPage();
}

void Courtroom::on_charselect_right_clicked()
{
  ++char_select_current_page;
  setCharSelectPage();
}

void Courtroom::on_changecharacter_clicked()
{
  //T0D0
  //politely tell the server that we're not using our char anymore(playerChar)
  //setCharSelect();
  ui->charselect->show();
}
