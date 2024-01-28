#ifndef TASKRUNNABLE_H
#define TASKRUNNABLE_H

#include <QRunnable>
#include <QTcpSocket>
#include <QCryptographicHash>
#include <QImage>
#include <QBuffer>
#include <QFile>
#include <QProcess>



enum class PythonProgram {ratios, corr};

class TaskRunnable : public QRunnable
{
public:
    TaskRunnable(QTcpSocket* socket, const QByteArray& arr, const PythonProgram& py, const QString& path);

    void run();

private:
    QTcpSocket* socket_;
    qintptr socketDesc;
    QByteArray array; // data sent by client
    QByteArray data_; // temporary data variable
    PythonProgram py_;
    QString path_;
    QString hash_;

    void CreateHash();
    void SendPng();
    void SendText();
    void StartGetRatios();
    void StartGetCorr();
    void DeletePngText();

    void SendToClient(const QString& command);
};

#endif // TASKRUNNABLE_H
