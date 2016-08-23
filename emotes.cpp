#include "emotes.h"

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
