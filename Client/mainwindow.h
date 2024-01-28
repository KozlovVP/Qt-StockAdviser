#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QFile>

class TaskWindow;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum class DataType {corr, ratios};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);

private slots:
    void handleConnected();
    void SendToServer(QString command, QByteArray data);

    void DisplayTextFromServer(const QByteArray& arr, const DataType& data);
    void DisplayPngFromServer(const QByteArray& arr);

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;

    QByteArray Data;
    quint32 m_nNextВlockSize = 0;

    QList<QString> tickers_;

public slots:
    void slotReadyRead();
};
#endif // MAINWINDOW_H
