#include "serverthread.h"


ServerThread::ServerThread(int fd, QObject *parent):QThread(parent)
{
    m_fd = fd;
}
void ServerThread::run()
{
    /* 在这个进程里，读取数据，写出数据 */
    qDebug("some one connected");
    QTcpSocket socket;
    /* 根据手册要这么使用 */
    if (!socket.setSocketDescriptor(m_fd)) {
        qDebug("Socket error!");
        return;
    }


    /*
        阻塞，等待数据的到来
    */
    socket.waitForReadyRead(-1);
    QByteArray rbuf = socket.readAll();
    //  we can check the socks version here
    qDebug("RCV:%s",rbuf.data());


    QTcpSocket sock;
    sock.connectToHost(QHostAddress("127.0.0.1"),8080);

    sockDateTurnel *tur1 = new sockDateTurnel(sock.socketDescriptor(),socket.socketDescriptor());
    sockDateTurnel *tur2 = new sockDateTurnel(socket.socketDescriptor(),sock.socketDescriptor());
    tur1->start();
    tur2->start();
    while(1){
        sleep(1);
        if(tur1->RunningNow()!=1 || tur2->RunningNow() !=1 ){
            // quit now ~
            tur1->terminate();
            tur2->terminate();
            break;
        }
   //  Thread waiting ~
    }
    /*
        等待数据写完，不加这个函数，接收方总是只能接收到空数据，长度为0
    */
    qDebug("\n one socks exit ! \n");


}


