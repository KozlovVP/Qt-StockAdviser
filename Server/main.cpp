#include "server.h"

#include <QApplication>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server w(QFileInfo(".").absolutePath());
    return a.exec();
}
