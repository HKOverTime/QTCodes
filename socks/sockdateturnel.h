#ifndef SOCKDATETURNEL_H
#define SOCKDATETURNEL_H
#include <QtNetwork>
#include <QThread>
#include <QDebug>

class sockDateTurnel : public QThread
{
    Q_OBJECT
public:
    sockDateTurnel(qintptr s1Descriptor, qintptr s2Descriptor);
    int RunningNow();
    void run();
private:
    qintptr s1d;
    qintptr s2d;
    QTcpSocket *in;
    QTcpSocket *out;
    QByteArray buffer;
    int run_state;

    void CloseSocks();

};

#endif // SOCKDATETURNEL_H
