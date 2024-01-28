#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleSheetFile(":/stylesheets/stylesheets/Fibrary.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.setWindowTitle("StockAdviser");
    w.setWindowIcon(QIcon(":/img/img/stock_png.jpg"));
    w.show();
    return a.exec();
}
