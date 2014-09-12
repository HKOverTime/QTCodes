#ifndef SERVER_H
#define SERVER_H
#include "serverthread.h"
class Server : public QTcpServer
{
public:
    Server();
private:
    /* 当产生一个新的连接的时候，会调用这个函数
       所以可以在我们定义的类中，把它改写覆盖掉，
       继承来的父类，这个函数是虚函数
     */
    void incomingConnection(qintptr sockDescriptor);
};

#endif // SERVER_H
