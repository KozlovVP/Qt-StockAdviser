#ifndef READRUNNABLE_H
#define READRUNNABLE_H

#include "taskrunnable.h"

#include <QRunnable>
#include <QString>
#include <QByteArray>
#include <QTcpSocket>
#include <QThreadPool>

class ReadRunnable : public QRunnable
{
public:
    ReadRunnable(QTcpSocket* socket, QThreadPool* threadP, const QString& path);

    void run();

private:
    QString command_;
    QByteArray array_;
    quint32 m_nNextВlockSize = 0;
    QString path_;

    QTcpSocket* socket_;
    QThreadPool* threadPool;
};

#endif // READRUNNABLE_H
