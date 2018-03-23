//
// Created by gil on 15/03/18.
//

#ifndef ABPYTOOLS_QT_ABNUMCONNECTIONWORKER_H
#define ABPYTOOLS_QT_ABNUMCONNECTIONWORKER_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QDebug>

#include "connection_check.h"

class abnumConnectionWorker: public QObject {

Q_OBJECT

public:
    abnumConnectionWorker() {};

private Q_SLOTS:
    void checkConnection();
    void checkConnectionHelper();

Q_SIGNALS:
    void connectionStatus(bool);

private:
    bool connected;
    QTimer *connectionTimer;
};


#endif //ABPYTOOLS_QT_ABNUMCONNECTIONWORKER_H