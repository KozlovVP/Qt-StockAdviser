#include "taskrunnable.h"

TaskRunnable::TaskRunnable(QTcpSocket* socket, const QByteArray& arr, const PythonProgram& py, const QString& path) :
    socket_(socket),
    array(arr),
    py_(py),
    path_(path)
{
    socketDesc = socket_->socketDescriptor();
}

void TaskRunnable::run() {
    CreateHash();

    switch (py_) {
        case PythonProgram::ratios:
            StartGetRatios();
            break;
        case PythonProgram::corr:
            StartGetCorr();
            break;
    }

    StartGetRatios(); // starts get_ratios.py

    SendPng();
    SendText();

    DeletePngText();
}

void TaskRunnable::CreateHash()
{
    QString socketDescriptorString = QString::number(socketDesc);
    QString word_to_hash = array + socketDescriptorString;
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(word_to_hash.toUtf8());
    QByteArray result = hash.result();
    hash_ = result.toHex();
}

void TaskRunnable::SendPng()
{
    QString filePath;
    switch (py_) {
    case PythonProgram::ratios:
        filePath = path_ + "/Server/get_ratios/" + hash_ + ".png";
        break;
    case PythonProgram::corr:
        filePath = path_ + "/Server/get_corr/" + hash_ + ".png";
    }

    QImage image(filePath);

    data_.clear();
    QBuffer buffer(&data_);
    buffer.open(QIODevice::ReadWrite);
    image.save(&buffer, "PNG");

    SendToClient("1");
}

void TaskRunnable::SendText()
{
    QString filePath;
    switch (py_) {
    case PythonProgram::ratios:
        filePath = path_ + "/Server/get_ratios/" + hash_ + ".txt";
        break;
    case PythonProgram::corr:
        filePath = path_ + "/Server/get_corr/" + hash_ + ".txt";
        break;
    }

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        qDebug() << filePath;
        QTextStream in(&file);
        QString ratios = in.readAll();
        qDebug() << ratios;
        data_.clear();
        data_ = ratios.toUtf8();
    }

    switch (py_) {
        case PythonProgram::ratios:
            SendToClient("23");
            break;
        case PythonProgram::corr:
            SendToClient("24");
            break;
    }
}

void TaskRunnable::StartGetRatios()
{
    QProcess* process = new QProcess;
    QStringList arguments;
    arguments << path_ + "/Server/get_ratios/get_ratios.py" << array << hash_;
    process->start("python", arguments);
    process->waitForFinished();
}

void TaskRunnable::StartGetCorr()
{
    QStringList tickerList = QString(array).split(" ");
    QString ticker1 = tickerList[0];
    QString ticker2 = tickerList[1];

    qDebug() << ticker1 << ticker2;

    QProcess* process = new QProcess;
    QStringList arguments;
    arguments << path_ + "/Server/get_corr/get_corr.py" << ticker1 << ticker2 << hash_;
    process->start("python", arguments);
    process->waitForFinished();
}

void TaskRunnable::DeletePngText()
{
    QFile::remove(path_ + "/Server/get_ratios/" + hash_ + ".png");
    QFile::remove(path_ + "/Server/get_ratios/" + hash_ + ".txt");

    QFile::remove(path_ + "/Server/get_corr/" + hash_ + ".png");
    QFile::remove(path_ + "/Server/get_corr/" + hash_ + ".txt");
}



void TaskRunnable::SendToClient(const QString &command)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint32(0) << command << data_;

    out.device()->seek(0);
    out << quint32(arrBlock.size() - sizeof(quint32));
    socket_->write(arrBlock);
    socket_->waitForBytesWritten();
}
