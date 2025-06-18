#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, &TcpClient::onErrorOccurred);
}

void TcpClient::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
}

void TcpClient::sendMessage(const QString &message)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QByteArray data = message.toUtf8();
        socket->write(data);
    }
}

void TcpClient::onConnected()
{
    qDebug() << "Connected to server";
    emit connected();
}

void TcpClient::onDisconnected()
{
    qDebug() << "Disconnected from server";
    emit disconnected();
}

void TcpClient::onReadyRead()
{
    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);
    qDebug() << "Received message:" << message;
    emit messageReceived(message);
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    QString errorStr = socket->errorString();
    qDebug() << "Error occurred:" << errorStr;
    emit errorOccurred(errorStr);
}
