#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QString>
#include <QMessageBox>

void callError(QString message, bool error_text = true);

void callError(int message);

void callFatalError(QString message, bool error_text = true);

#endif // ERRORHANDLER_H
