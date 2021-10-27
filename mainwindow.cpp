#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Windows.h>
#include <stdio.h>
#include <Psapi.h>
#include <QDateTime>
#include <QDebug>
#include <QSharedPointer>
#include <QBrush>
#include <QPen>


int MainWindow::currentNum_ = 0;
qint64 MainWindow::startTime_ = 0;
qint64 MainWindow::currentTime_ = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , thread_getFrame(new QThread)
    , thread_io_(new QThread)
    , data_(new PlotObject)
    , log_io_(new LogObject)
    , listModel_(new QStringListModel(this))
{
    // UI
    ui->setupUi(this);
	ui->timeInterEdit->setText(QString::number(1000));
    ui->graphInterEdit->setText(QString::number(2000));
    connect(ui->clearBtn, &QPushButton::clicked, this, &MainWindow::onClearGraph);
    this->setWindowTitle("GetPrivateBytes v" + QString::number(VERSION_MAJOR)+ "."
                         +  QString::number(VERSION_MINOR)
                         + " | Boot Time: "
                         + QDateTime::currentDateTime().toString("yyyy-MM-dd-HH:mm:ss"));
    this->setWindowIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap)40));
    // Timer
    timer_ = new QTimer;
    timer_update_ = new QTimer;
  
    // Get Private bytes from Thread
    data_->moveToThread(thread_getFrame);
    log_io_->moveToThread(thread_io_);
    thread_getFrame->start();
    thread_io_->start();
    connect(ui->processIdEdit, &QLineEdit::textChanged, data_, &PlotObject::setProcessId);  // set processID to query
    connect(ui->processIdEdit, &QLineEdit::textChanged, this, &MainWindow::setComboBoxIndex);  // set processID to refresh pid name
    connect(ui->startBtn, &QPushButton::clicked, this, &MainWindow::onStart);
    connect(ui->stopBtn, &QPushButton::clicked, this, &MainWindow::onStop);
    connect(ui->refreshGraphBtn, &QPushButton::clicked, this, &MainWindow::refreshData);
    connect(ui->refreshProcessBtn, &QPushButton::clicked, this, &MainWindow::getProcessMap);
    connect(timer_, &QTimer::timeout, data_, &PlotObject::getProcessStatus);
    connect(timer_update_, &QTimer::timeout, this, &MainWindow::refreshData);
    connect(data_, &PlotObject::sigPrivateBytes, this, &MainWindow::drawData, Qt::QueuedConnection);
    connect(data_, &PlotObject::sigInexistence, this, &MainWindow::onMessageBox);
    connect(this, &MainWindow::sigForLog, log_io_, &LogObject::writeLog, Qt::QueuedConnection);

    // CustomPlot
    init_graph();

    // ComboBox
    ui->comboBox->setModel(listModel_);
    getProcessMap();
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::onSetCurrentProcessId);
    ui->comboBox->setEditable(false);

    // Spin box
    //connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, QOverload<int>::of(&MainWindow::setBufferNum));
}

MainWindow::~MainWindow()
{
    delete ui;
    timer_->stop(); delete timer_;
    timer_update_->stop(); delete timer_update_;
    thread_getFrame->terminate(); delete thread_getFrame; thread_getFrame  = nullptr;
    thread_io_->terminate(); delete thread_io_;thread_io_  = nullptr;
    delete log_io_;log_io_  = nullptr;
    delete listModel_;listModel_  = nullptr;
}

void MainWindow::init_graph()
{
    ui->customPlot->addGraph();
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );  // | QCP::iSelectPlottables 不可选中
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue, 1));
    //ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot, QPen(Qt::yellow, 100), QBrush(Qt::yellow), 100));
    //ui->customPlot->graph(0)->rescaleAxes(false);
    //ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    dateTicker = QSharedPointer<QCPAxisTickerDateTime>(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("MM-dd hh:mm:ss:zzz");
    ui->customPlot->xAxis->setTicker(dateTicker);
    mData_ = ui->customPlot->graph(0)->data()->coreData();  // user-defined api(change src), qcustomplot.h:line 2594
    //mData->clear();
    // set background color
    //QBrush backRole;
    //backRole.setColor("skyblue");
    //backRole.setStyle(Qt::SolidPattern);
    //ui->customPlot->setBackground(backRole);
    ui->customPlot->xAxis->setTickLabelRotation(5);
    //ui->customPlot->xAxis->setNumberPrecision(1);
    ui->customPlot->xAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);
}

void MainWindow::disableUI(bool flag)
{
    ui->processIdEdit->setEnabled(!flag);
    ui->refreshProcessBtn->setEnabled(!flag);
    ui->comboBox->setEnabled(!flag);
    ui->timeInterEdit->setEnabled(!flag);
    ui->graphInterEdit->setEnabled(!flag);
    ui->spinBox->setEnabled(!flag);
    ui->startBtn->setEnabled(!flag);
}

void MainWindow::drawData(Frame frame)
{
    // Data
    currentTime_ = (double)QDateTime::currentMSecsSinceEpoch()  / 1000.0f;
    unsigned long data =  frame.private_bytes / 1024;

    // Axis X
    if (currentNum_ >= bufferNum_)
    {
        mData_->removeFirst();
        currentNum_--;
    }

    if ((int)data < min_ ) min_ = data;
    else if ((int)data > max_ ) max_ = data;

    QCPGraphData newPoint;
    newPoint.key = (double)currentTime_;
    newPoint.value = (double)data;
    mData_->append(newPoint);
    currentNum_++;
    if (currentNum_ == 1) { min_ = data -5 ;max_ = data - 5;}
    int count = ui->customPlot->graph(0)->dataCount();
    ui->statusbar->showMessage("Count: " + QString::number(count));

    QString log = QString(QDateTime::currentDateTime().toString("MM-dd,HH:mm:ss:zzz")) + "," + QString::number(currentId_) + "," + QString::number(data) + "\n";
    emit sigForLog(log);
}

void MainWindow::onStart()
{
    // get parameters from UI
	if (ui->timeInterEdit->text().isEmpty())
		ui->timeInterEdit->setText(QString::number(1000));
	if (ui->graphInterEdit->text().isEmpty())
        ui->graphInterEdit->setText(QString::number(2000));

	int processRefreshTime = ui->timeInterEdit->text().toInt();
    int graphRefreshTime = ui->graphInterEdit->text().toInt();

    bufferNum_ = ui->spinBox->value(); // to ms

    mData_->reserve(ui->spinBox->value());

	timer_->setInterval(processRefreshTime);
	timer_update_->setInterval(graphRefreshTime);

    if (ui->processIdEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Waring", "Please input/select process name/id");
        return;
    }

    // set customplot Axis
    startTime_ = (double)QDateTime::currentMSecsSinceEpoch()  / 1000.0f;

    //    ui->customPlot->xAxis->setRange(startTime_, startTime_ + bufferNum_);
    ui->customPlot->yAxis->setRange(min_,max_);

    // UI
    disableUI(true);

    // Timer start
    timer_->start();
    timer_update_->start();
}

void MainWindow::onStop()
{
    timer_->stop();
    timer_update_->stop();
    disableUI(false);
}

void MainWindow::refreshData()
{
    if (mData_->size()  == 1 )
    {

    }
    if (mData_->size() > 0)
        ui->customPlot->xAxis->setRange((double)(*mData_)[0].mainKey(), (double)currentTime_);
    ui->customPlot->yAxis->setRange(min_,max_);
    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
}

void MainWindow::getProcessMap()
{
	DWORD aProcesses[1024];
	DWORD cbNeeded;
	DWORD cProcesses;
	unsigned int i;
    processMap_.clear();
    processList_.clear();

	// Get the list of process identifiers.
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		return;
	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the names of the modules for each process.
	for (i = 0; i < cProcesses; i++)
	{
		DWORD processID = aProcesses[i];
		if (processID == '0')
			continue;
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 0, processID);
		wchar_t buffer[50];
        DWORD ret = GetModuleBaseNameW(hProcess, nullptr, buffer, 50);
		CloseHandle(hProcess);
        // GetModuleBaseNameW fails when ret is 0
        if (ret !=0 )
        {
            QString key = QString::fromWCharArray(buffer) + " | " + QString::number(processID); // 防止重名进程
            processMap_.insert(key, (int)processID);
            processList_ << key;
        }
	}
    processList_.sort(Qt::CaseInsensitive);
    listModel_->setStringList(processList_);
}

void MainWindow::onSetCurrentProcessId(QString processName)
{
    // after refreshing, set id=0
    if (processName.isEmpty())
    {
        currentId_ = 0;
        ui->processIdEdit->clear();
    }
    else
    {
        currentId_ = processMap_.value(processName);
        ui->comboBox->setCurrentText(processName);
        ui->processIdEdit->setText(QString::number(currentId_));
    }
}

void MainWindow::onClearGraph()
{
    //ui->customPlot->graph(0)->data().data()->clear();  // same as: mData->clear();
    mData_->clear();
    currentNum_ = 0;
    int count = ui->customPlot->graph(0)->dataCount();
    ui->statusbar->showMessage("Count: " + QString::number(count));
    this->refreshData();
//    startTime_ = (double)QDateTime::currentMSecsSinceEpoch();
//    ui->customPlot->xAxis->setRange(startTime_, startTime_ + bufferNum_);
}

void MainWindow::onMessageBox(QString msg)
{
    this->onStop();
    QMessageBox::warning(this, "Warning", msg);
}

void MainWindow::setComboBoxIndex(QString inputId)
{
    int id = inputId.toInt();
    auto iter = processMap_.begin();
    QString key = "";
    while (iter != processMap_.end())
    {
        if (iter.value() == id)
            key = iter.key();
        iter++;
    }
    if (key.isEmpty())
       ui->comboBox->setCurrentIndex(-1);
    else
        ui->comboBox->setCurrentText(key);
}
