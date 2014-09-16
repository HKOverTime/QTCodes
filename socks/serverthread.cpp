#include "serverthread.h"

void mprint (QByteArray a){
    int len =  a.length();
    for(int i=0;i<len;i++){
        qDebug()<<QString::number(a.at(i));
    }
}

QByteArray IPtoBytes(QString mip) {
    QStringList b=mip.split(".");
    QByteArray res ;
    res.resize(4);
    for (int i=0;i<4;i++){
        res[i]= b[i].toInt();
     //  qDebug()<< (int)res[i];
    }
    return res;
}

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

    //  we can check the socks version here
    socket.waitForReadyRead(-1);
 //   QByteArray rbuf = socket.readAll();
 //   qDebug("RCV:%s",rbuf.data());

    QByteArray rbuf = socket.readAll();
    QByteArray rep_req;
    rep_req.resize(2);
    rep_req[0] = 0x05;
    rep_req[1] = 0x00;

    socket.write(rep_req);
    socket.waitForBytesWritten(-1);
    // 2. Request
    socket.waitForReadyRead(-1);
    rbuf = socket.readAll();
    qDebug() << "Request now !!";
    char mode = rbuf.at(1);
    QString address ;
    int len;
    if (rbuf.at(3)==0x01){
        // ipv4
        qDebug() << "ipv4 !!"<< endl;
        unsigned addr = 0;
        for ( int j = 4;j<8;j++){
            char c = rbuf.at(j);
            addr = addr*256+ c;
        }
        address = QHostAddress(addr).toString();
        len = 4+4;  // head 4byte + ip  4byte
    }
    else if (rbuf.at(3) == 0x03){
        qDebug() << "host string !!"<< endl;
        QString adr;
        len = rbuf.at(4);
        adr = rbuf.remove(0,5);
        adr = adr.remove(len,adr.length()-len);
        address = QString(adr);
    }

    unsigned port = rbuf.at(len)*256+rbuf.at(len+1);
    QByteArray reply ;
    reply.resize(4);
    //  05 00 00 01
    reply[0] = 0x05;reply[1] = 0x00;reply[2] = 0x00;reply[3] = 0x01;
    //  may be has some exception
    QTcpSocket sock;
    if (mode == 0x01){
        qDebug()<<"mode == 1? ?";
        //  need reslove some DNS problem
        sock.connectToHost(address,port);
        if(!sock.waitForConnected(3000)){
            qDebug()<< address << port;
            qDebug()<< address.length();
            qDebug()<< "Cannot creat the connect ~ close now!";
            return ;

        }
        else{
            qDebug()<<QString("Tcp connect to ")<<sock.localAddress().toString()<<QString(" ")<< sock.localPort();
        }
    }
    else{
        qDebug()<<"mode != 1 ??";
        reply.resize(4);
        // 05 07 00 01
        reply[0] = 0x05;reply[1] = 0x07;reply[2] = 0x00;reply[3] = 0x01;
        sock.write(reply);
        sock.waitForBytesWritten(-1);
        return ;
        // Command not supported
    }
    reply =reply +QByteArray("\x41\x41\x41\x41\x41\x41");

    mprint(reply);
    socket.write(reply);
    socket.waitForBytesWritten(-1);

 //   sock.connectToHost(QHostAddress("127.0.0.1"),8080);

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


