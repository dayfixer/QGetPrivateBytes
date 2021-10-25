#include "mainwindow.h"

#include <QApplication>
#include <QProcess>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QProcess process;
    process.start("tasklist.exe");
    if(process.waitForFinished())
    {
        QByteArray result = process.readAll();
            qDebug() << result;
    }



    return a.exec();
}
