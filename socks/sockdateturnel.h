#ifndef SOCKDATETURNEL_H
#define SOCKDATETURNEL_H
#include <QtNetwork>
#include <QThread>
#include <QDebug>

class sockDateTurnel : public QThread
{
public:
    sockDateTurnel(qintptr s1Descriptor, qintptr s2Descriptor);
    void run();
private:
    qintptr s1d;
    qintptr s2d;
    QTcpSocket *in;
    QTcpSocket *out;
    QByteArray buffer;
};

#endif // SOCKDATETURNEL_H
