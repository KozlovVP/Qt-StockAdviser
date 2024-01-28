#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QBuffer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 2323);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    connect(socket, &QTcpSocket::connected, this, &MainWindow::handleConnected);
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    QFile file(":/tickers/tickers/tickers.csv");
    QTextStream in(&file);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!in.atEnd())
        {
            QString line = in.readLine();
            tickers_.append(line.split(',')[0]);
        }
    }

    this->setFixedSize(400, 400);
    ui->label_2->setVisible(false);
    ui->label->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);
    ui->pushButton_5->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
}

void MainWindow::SendToServer(QString command, QByteArray data) {
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint32(0) << command << data;

    out.device()->seek(0);
    out << quint32(arrBlock.size() - sizeof(quint32));
    socket->write(arrBlock);
    socket->waitForBytesWritten();
}

void MainWindow::DisplayTextFromServer(const QByteArray &arr, const DataType& data)
{
    ui->label_5->setVisible(false);
    QString str = arr;
    if (arr == "") {
        this->ui->label_2->setText("Unfortunately server failed\nto find any ratio data");
    }
    else {
        switch (data) {
            case DataType::corr:
                this->ui->label_2->setText("Estimated correlation is " + arr);
                ui->label_2->setVisible(true);
                break;
            case DataType::ratios:
                QVector<QString> ratioVector = str.split(' ');
                QString text;
                text += "Useful fundamental analysis ratios:\n\n";
                for (const QString& str : ratioVector) {
                    int colonPos = str.indexOf(':');
                    QString beforeColon = str.left(colonPos);
                    QString afterColon = str.mid(colonPos + 1);
                    //qDebug() << charactersBeforeColon << charactersAfterColon;
                    if (beforeColon == "wcr") {
                        text += "working capital ratio = " + afterColon + "\n";
                    }
                    else if (beforeColon == "dr") {
                        text += "debt ratio = " + afterColon + "\n";
                    }
                    else if (beforeColon == "qr") {
                        text += "quick ratio = " + afterColon + "\n";
                    }
                    else if (beforeColon == "at"){
                        text += "acid test formula = " + afterColon;
                    }
                    qDebug() << text;
                    ui->label_2->setText(text);
                    ui->label_2->setVisible(true);
                }
        }
    }
}

void MainWindow::DisplayPngFromServer(const QByteArray &arr)
{
    QImage receivedImage;
    receivedImage.loadFromData(arr);
    QPixmap pixmap = QPixmap::fromImage(receivedImage);
    int w = this->ui->label->width();
    int h = this->ui->label->height();

    ui->label->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->label->setVisible(true);
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);

    if (in.status() == QDataStream::Ok) {
        QString command;
        QByteArray array;
        for (;;) {
            if (!m_nNextВlockSize) {
                if (socket->bytesAvailable() < sizeof(quint32)) {
                    break;
                }
            in >> m_nNextВlockSize;
            }
            if (socket->bytesAvailable() < m_nNextВlockSize) {
                break;
            }
            in >> command;
            if (command == "1") {
                in >> array;
            }
            else {
                in >> array;
            }
            m_nNextВlockSize = 0;
        }

        if (command == "1") {
            DisplayPngFromServer(array);
        }
        else if (command == "23") {
            DisplayTextFromServer(array, DataType::ratios);
        }
        else if (command == "24"){
            DisplayTextFromServer(array, DataType::corr);
        }
    }
}

void MainWindow::handleConnected() {
    qDebug() << "Connected to server";
}

void MainWindow::onSocketStateChanged(QAbstractSocket::SocketState socketState) {
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->label_4->setVisible(true);
    ui->lineEdit->setVisible(true);
    ui->pushButton_3->setVisible(true);
    ui->pushButton_4->setVisible(true);
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);

    ui->lineEdit->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);

    ui->label_3->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->pushButton_5->setVisible(false);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();

    ui->pushButton->setVisible(true);
    ui->pushButton_2->setVisible(true);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->label_5->setVisible(true);
    QString ticker = ui->lineEdit->text();
    ticker.remove(" ");
    if (tickers_.contains(ticker)) {
        SendToServer("1", ticker.toUtf8());
    }
    else {
        QMessageBox::warning(this, "Ticker", "No such ticker");
        ui->label_5->setVisible(false);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);

    ui->label_3->setVisible(true);
    ui->lineEdit->setVisible(true);
    ui->lineEdit_2->setVisible(true);
    ui->pushButton_5->setVisible(true);
    ui->pushButton_4->setVisible(true);
}


void MainWindow::on_pushButton_5_clicked()
{
    QString ticker1 = ui->lineEdit->text();
    ticker1.remove(" ");
    QString ticker2 = ui->lineEdit_2->text();
    ticker2.remove(" ");

    ui->label_5->setVisible(true);

    if (tickers_.contains(ticker1) && tickers_.contains(ticker2)) {
        QString to_send = ticker1 + " " + ticker2;
        qDebug() << to_send;
        SendToServer("2", to_send.toUtf8());
    }
    else {
        QMessageBox::warning(this, "Ticker", "No such ticker(s)");
        ui->label_5->setVisible(false);
    }
}

