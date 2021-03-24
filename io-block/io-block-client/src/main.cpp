#include <QCoreApplication>
#include "DTcpClient.h"
#include <QDebug>

int main(int argc, char *argv[])
{

    DTcpClient client;
    if (!client.ConnectToServer("127.0.0.1", 9988)) {
        qInfo() << " Failed to connect to server *************";
        return 0;
    }

    char ch[1024];
    for (int i = 0; i < 10; i++) {
        memset(ch, 0, sizeof(ch));
        sprintf(ch, "Send msg ******* %d", i);
        client.Write(ch, strlen(ch));

        memset(ch, 0, sizeof(ch));
        client.Read(ch, 10);
        qInfo() << QString::fromLocal8Bit(ch);
    }

    client.Close();
}
