//
// Created by gil on 15/03/18.
//

#include "../include/abnumConnectionWorker.h"

void abnumConnectionWorker::checkConnection() {

    checkConnectionHelper();
    // run timer in background
    connectionTimer = new QTimer();
    connectionTimer->start(500);
    connect(connectionTimer, SIGNAL(timeout()), this, SLOT(checkConnectionHelper()));
}

void abnumConnectionWorker::checkConnectionHelper() {

    connected = abnumConnection();

    qDebug() << "Thread [" << thread()->currentThread() << "] says abnum is connected: " << connected;

    Q_EMIT(connectionStatus(connected));
}
