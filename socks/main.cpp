#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    /* 监听了所有网络接口，9876端口 */
    if ( !server.listen(QHostAddress::Any, 9876)) {
        qCritical("Cannot listen to port 9876.");
        server.close();
        return 1;
    }
    return a.exec();
}

