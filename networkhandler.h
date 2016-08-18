#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QTcpSocket>

class Networkhandler : public QObject
{
  Q_OBJECT

public:
  explicit Networkhandler(QObject *parent = 0);
  ~Networkhandler();

  QTcpSocket ms_socket;
  QTcpSocket server_socket;

  bool master_connected = false;
  bool server_connected = false;

signals:

public slots:
};

#endif // NETWORKHANDLER_H
