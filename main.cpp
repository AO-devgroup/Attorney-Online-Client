#include "main.h"

int main(int argc, char *argv[])
{

  QApplication main_application(argc, argv);

  set_theme_path();

  Lobby main_lobby;
  Courtroom main_courtroom;
  Networkhandler main_networkhandler;

  main_courtroom.hide();
  //main_courtroom.show();

  QObject::connect(&main_networkhandler, SIGNAL(ms_message_received(QString)), &main_lobby, SLOT(handle_ms_message(QString)));
  QObject::connect(&main_networkhandler, SIGNAL(server_list_received(QVector<server_type>&)), &main_lobby, SLOT(update_server_list(QVector<server_type>&)));
  QObject::connect(&main_networkhandler, SIGNAL(onlinestatus_changed(QString,QString)), &main_lobby, SLOT(update_onlinestatus(QString,QString)));

  QObject::connect(&main_networkhandler, SIGNAL(character_list_received(QVector<char_type>&)), &main_courtroom, SLOT(set_character_list(QVector<char_type>&)));
  QObject::connect(&main_networkhandler, SIGNAL(taken_list_received(QVector<int>&)), &main_courtroom, SLOT(set_taken_list(QVector<int>&)));
  QObject::connect(&main_networkhandler, SIGNAL(music_list_received(QStringList&)), &main_courtroom, SLOT(set_music_list(QStringList&)));
  QObject::connect(&main_networkhandler, SIGNAL(area_list_received(QVector<area_type>&)), &main_courtroom, SLOT(set_area_list(QVector<area_type>&)));
  QObject::connect(&main_networkhandler, SIGNAL(area_taken_list_received(QVector<int>&)), &main_courtroom, SLOT(set_area_taken_list(QVector<int>&)));
  //QObject::connect(&main_networkhandler, SIGNAL(chatmessage_received(chatmessage_type&)), &main_courtroom, SLOT(handle_chatmessage(chatmessage_type&)));
  QObject::connect(&main_networkhandler, SIGNAL(done_signal()), &main_courtroom, SLOT(go_to_charselect()));
  QObject::connect(&main_networkhandler, SIGNAL(character_reply_received(int,int)), &main_courtroom, SLOT(set_character(int,int)));
  QObject::connect(&main_networkhandler, SIGNAL(ms_message_received(QString)), &main_courtroom, SLOT(handle_ms_message(QString)));
  QObject::connect(&main_networkhandler, SIGNAL(ooc_message_received(QString)), &main_courtroom, SLOT(handle_ooc_message(QString)));
  QObject::connect(&main_networkhandler, SIGNAL(server_packet_received(QString)), &main_courtroom, SLOT(handle_server_packet(QString)));

  QObject::connect(&main_lobby, SIGNAL(all_servers_requested()), &main_networkhandler, SLOT(handle_all_servers_requested()));
  QObject::connect(&main_lobby, SIGNAL(server_connection_requested(QString,int)), &main_networkhandler, SLOT(connect_to_server(QString,int)));
  QObject::connect(&main_lobby, SIGNAL(ms_message_requested(QString)), &main_networkhandler, SLOT(ms_send_message(QString)));
  QObject::connect(&main_lobby, SIGNAL(enter_server_requested()), &main_networkhandler, SLOT(handle_enter_server_request()));

  QObject::connect(&main_courtroom, SIGNAL(character_requested(int,QString)), &main_networkhandler, SLOT(handle_character_request(int,QString)));
  QObject::connect(&main_courtroom, SIGNAL(chatmessage_requested(chatmessage_type&)), &main_networkhandler, SLOT(handle_chatmessage_request(chatmessage_type&)));
  QObject::connect(&main_courtroom, SIGNAL(legacy_chatmessage_requested(chatmessage_type&)), &main_networkhandler, SLOT(handle_legacy_chatmessage_request(chatmessage_type&)));
  QObject::connect(&main_courtroom, SIGNAL(ms_message_requested(QString)), &main_networkhandler, SLOT(ms_send_message(QString)));
  QObject::connect(&main_courtroom, SIGNAL(ooc_message_requested(QString)), &main_networkhandler, SLOT(ooc_send_message(QString)));
  QObject::connect(&main_courtroom, SIGNAL(song_requested(QString)), &main_networkhandler, SLOT(handle_song_request(QString)));
  QObject::connect(&main_courtroom, SIGNAL(request_packet(QString)), &main_networkhandler, SLOT(send_packet(QString)));
  QObject::connect(&main_courtroom, SIGNAL(close_socket_request()), &main_networkhandler, SLOT(close_socket()));

  QObject::connect(&main_courtroom, SIGNAL(entering_server()), &main_lobby, SLOT(handle_server_entry()));
  QObject::connect(&main_courtroom, SIGNAL(leaving_server()), &main_lobby, SLOT(handle_server_exit()));

  QObject::connect(&main_networkhandler, SIGNAL(request_quit()), &main_application, SLOT(quit()));

  main_networkhandler.connect_to_master();

  main_lobby.setTheme();

  main_lobby.show();

  return main_application.exec();
}
