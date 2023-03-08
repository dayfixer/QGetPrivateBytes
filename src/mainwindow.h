#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"
#include "plotobject.h"
#include "logobject.h"
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
    void init_graph();
    void drawData(Frame);
    void refreshData();
    void getProcessMap();
    void setComboBoxIndex(QString);
    void disableUI(bool flag);

    void onStart();
    void onStop();
    void onSetCurrentProcessId(QString);
    void onClearGraph();
    void onMessageBox(QString msg);
private:
    Ui::MainWindow *ui;

    QTimer* timer_;
    QTimer* timer_update_;
    QThread* thread_getFrame;
    QThread* thread_io_;
    PlotObject* data_;
    LogObject* log_io_;
    QSharedPointer<QCPAxisTickerDateTime> dateTicker;
    QMap<QString, int> processMap_;
    QStringList processList_;
    int currentId_;

    QStringListModel* listModel_;
    volatile int bufferNum_;
    QVector<QCPGraphData>* mData_ = nullptr;

    static int currentNum_;
    static qint64 startTime_;
    static qint64 currentTime_;

    int max_ = 0;
    int min_ = 0;
signals:
    void sigPrivateBytes(Frame);
    void sigForLog(QString);
};
#endif // MAINWINDOW_H
