#include "server.h"

#include <QDebug>
#include <QHostAddress>
#include <QAbstractSocket>

Server::Server(const QString& path) :
    server_(this),
    path_(path)
{
    threadPool = new QThreadPool(this);
    threadPool->setMaxThreadCount(QThread::idealThreadCount());

    server_.listen(QHostAddress::Any, 2323);
    connect(&server_, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

Server::~Server()
{
    qDebug() << "server break";
}

void Server::onNewConnection()
{
    QTcpSocket *clientSocket = server_.nextPendingConnection();
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    qDebug() << clientSocket << "connected";
}

void Server::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        return;
    }
}

void Server::onReadyRead()
{
    ReadRunnable* read = new ReadRunnable((QTcpSocket*)sender(), threadPool, path_);
    threadPool->start(read);
}
