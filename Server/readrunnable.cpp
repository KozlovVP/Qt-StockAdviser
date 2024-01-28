#include "readrunnable.h"

ReadRunnable::ReadRunnable(QTcpSocket* socket, QThreadPool* threadP, const QString& path) :
    path_(path),
    socket_(socket),
    threadPool(threadP)
{}

void ReadRunnable::run()
{
    QDataStream in(socket_);
    in.setVersion(QDataStream::Qt_6_2);

    for (;;) {
        if (!m_nNextВlockSize) {
            if (socket_->bytesAvailable() < sizeof(quint32)) {
                break;
            }
            in >> m_nNextВlockSize;
        }
        if (socket_->bytesAvailable() < m_nNextВlockSize) {
            break;
        }
        in >> command_ >> array_;
        m_nNextВlockSize = 0;
    }
    qDebug() << command_ << array_;

    if (command_ == "1") {
        TaskRunnable* task = new TaskRunnable(socket_, array_, PythonProgram::ratios, path_);
        threadPool->start(task);
    }

    if (command_ == "2") {
        TaskRunnable* task = new TaskRunnable(socket_, array_, PythonProgram::corr, path_);
        threadPool->start(task);
    }
}



