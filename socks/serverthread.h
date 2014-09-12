#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H
#include <QtNetwork>
#include <QThread>
#include <QDebug>
#include "sockdateturnel.h"
class ServerThread:public QThread
{
public:
    ServerThread(int fd, QObject *parent);
    void run();
private:
    int m_fd;
};

#endif // SERVERTHREAD_H
