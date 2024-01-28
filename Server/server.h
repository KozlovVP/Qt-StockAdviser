#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "readrunnable.h"

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QByteArray>
#include <QBuffer>
#include <QFile>
#include <QThreadPool>

#include <QProcess>
#include <QCryptographicHash>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(const QString& path);
    ~Server();

    QTcpSocket *socket;

public slots:
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();

private slots:

private:
    QTcpServer  server_;

    QByteArray data_;
    quint32 m_nNextВlockSize = 0;
    QString path_;

    QThreadPool* threadPool;
};

#endif // MAINWINDOW_H
