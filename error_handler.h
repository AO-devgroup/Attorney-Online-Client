#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QString>
#include <QMessageBox>

void callError(QString message);

void callError(int message);

void callFatalError(QString message);

#endif // ERRORHANDLER_H
