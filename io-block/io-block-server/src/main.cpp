#include <QCoreApplication>
#include "DTcpServer.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    DTcpServer server;
    if (!server.InitServer(9988)) {
        qInfo() << " Failed to InitServer ****************************";
        return 0;
    }

    if (!server.Accept()) {
        qInfo() << " Failed to Accept client *************************";
        return 0;
    }

    char buf[1024];
    while (true) {
        memset(buf, 0, sizeof(buf));
        if (server.Read(buf, 10) == false) {
            break;
        }
        qInfo() << QString::fromLocal8Bit(buf);

        strcat(buf, "****OK");
        if (server.Write(buf) == false) {
            break;
        }
    }

    qInfo() << " break ***************** ";
    server.CloseListen();
    server.CloseClient();
    qInfo() << " break ***************** ";

    return 0;//a.exec();
}
