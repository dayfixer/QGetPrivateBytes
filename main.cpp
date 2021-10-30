#include "mainwindow.h"

#include <QApplication>
#include <QProcess>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QTranslator* qtTranslator = new QTranslator;
	if (qtTranslator->load("./translations/QGetPrivateByte_Zh_cn.qm")) {
		a.installTranslator(qtTranslator);
	}

    MainWindow w;
    w.show();

    return a.exec();
}
