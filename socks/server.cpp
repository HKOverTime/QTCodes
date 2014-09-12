#include "server.h"

Server::Server():QTcpServer()
{
}
void Server::incomingConnection(qintptr sockDescriptor)
{
    /* 在这里面开辟一个线程来处理连接 */
    ServerThread *thread = new ServerThread(sockDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
