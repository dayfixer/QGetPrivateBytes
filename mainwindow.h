#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"
#include "plotobject.h"
#include "qcustomplot.h"

#include <QMainWindow>
#include <QTimer>
#include <QMetaType>
#include <QFile>
#include <QThread>
#include "QStringListModel"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void drawData(Frame);
    void onStart();
    void onStop();
    void refreshData();
    void getProcessMap();
    void onSetCurrentProcessId(QString);
    void onClearGraph();
private:
    Ui::MainWindow *ui;

    QTimer* timer_;
    QTimer* timer_update_;
    QFile* file_;
    QThread* thread_;
    PlotObject* data_;
    QSharedPointer<QCPAxisTickerDateTime> dateTicker;
    QMap<QString, int> processMap_;
    QStringList processList_;

    QStringListModel* listModel_;
signals:
    void sigPrivateBytes(Frame);
};
#endif // MAINWINDOW_H
