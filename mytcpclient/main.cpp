#include <QCoreApplication>
#include "tcpclient.h"

//simple main

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpClient client;

    // Подключаем сигналы клиента
    QObject::connect(&client, &TcpClient::connected, []() {
        qDebug() << "Connected signal received!";
    });

    QObject::connect(&client, &TcpClient::disconnected, []() {
        qDebug() << "Disconnected signal received!";
    });

    QObject::connect(&client, &TcpClient::messageReceived, [](const QString &msg) {
        qDebug() << "Message received:" << msg;
    });

    QObject::connect(&client, &TcpClient::errorOccurred, [](const QString &error) {
        qDebug() << "Error:" << error;
    });

    // Подключаемся к серверу
    client.connectToServer("localhost", 6000);

    // Отправляем сообщение после подключения
    QObject::connect(&client, &TcpClient::connected, [&client]() {
        client.sendMessage("Hello from Qt client!");
    });

    return a.exec();
}
