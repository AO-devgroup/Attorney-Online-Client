#include "main.h"

int main(int argc, char *argv[])
{

  QApplication main_application(argc, argv);

  Lobby main_lobby;
  Courtroom main_courtroom;
  Networkhandler main_networkhandler;

  main_courtroom.hide();

  QObject::connect(&main_networkhandler, SIGNAL(ms_message_received(QString)), &main_lobby, SLOT(handle_ms_message(QString)));
  QObject::connect(&main_networkhandler, SIGNAL(server_list_received(QVector<server_type>&)), &main_lobby, SLOT(update_server_list(QVector<server_type>&)));
  QObject::connect(&main_networkhandler, SIGNAL(onlinestatus_changed(QString,QString)), &main_lobby, SLOT(update_onlinestatus(QString,QString)));

  QObject::connect(&main_networkhandler, SIGNAL(done_loading()), &main_courtroom, SLOT(initialize_courtroom()));
  QObject::connect(&main_networkhandler, SIGNAL(character_list_received(QVector<char_type>&)), &main_courtroom, SLOT(set_character_list(QVector<char_type>&)));
  QObject::connect(&main_networkhandler, SIGNAL(music_list_received(QStringList&)), &main_courtroom, SLOT(set_music_list(QStringList&)));

  QObject::connect(&main_lobby, SIGNAL(all_servers_requested()), &main_networkhandler, SLOT(handle_all_servers_requested()));
  QObject::connect(&main_lobby, SIGNAL(server_connection_requested(QString,int)), &main_networkhandler, SLOT(connect_to_server(QString,int)));
  QObject::connect(&main_lobby, SIGNAL(ms_message_requested(QString)), &main_networkhandler, SLOT(ms_send_message(QString)));
  QObject::connect(&main_lobby, SIGNAL(enter_server_requested()), &main_networkhandler, SLOT(handle_enter_server_request()));

  main_networkhandler.connect_to_master();

  LoadConfig();
  main_lobby.setTheme();

  main_lobby.show();

  return main_application.exec();
}
