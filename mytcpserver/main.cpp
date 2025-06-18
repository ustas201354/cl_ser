#include <QCoreApplication>
#include "mytcpserver.h"

# It's simple code

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer server;

    return a.exec();
}
