#include "serverthread.h"


ServerThread::ServerThread(int fd, QObject *parent):QThread(parent)
{
    m_fd = fd;
}
void ServerThread::run()
{
    /* 在这个进程里，读取数据，写出数据 */
    qDebug("I'm Here");
    QTcpSocket socket;
    /* 根据手册要这么使用 */
    if (!socket.setSocketDescriptor(m_fd)) {
        qDebug("Socket error!");

        return;
    }
#if 1
    /*
        阻塞，等待数据的到来
    */
    socket.waitForReadyRead(-1);
    QByteArray rbuf = socket.readAll();
    qDebug("RCV:%s",rbuf.data());
#endif
#if 1
    QTcpSocket sock;
    sock.connectToHost(QHostAddress("127.0.0.1"),8080);



    sockDateTurnel *tur1 = new sockDateTurnel(sock.socketDescriptor(),socket.socketDescriptor());
    sockDateTurnel *tur2 = new sockDateTurnel(socket.socketDescriptor(),sock.socketDescriptor());
    tur1->start();
    tur2->start();
    tur1->wait();
    tur2->wait();

    /*
        等待数据写完，不加这个函数，接收方总是只能接收到空数据，长度为0
    */
    qDebug("\nClosed ? \n");
#endif
}

