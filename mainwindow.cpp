#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Windows.h>
#include <stdio.h>
#include <Psapi.h>
#include <QDateTime>
#include <QDebug>
#include <QSharedPointer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , thread_(new QThread)
    , data_(new PlotObject)
    , listModel_(new QStringListModel(this))
{
    // UI
    ui->setupUi(this);
	ui->timeInterEdit->setText(QString::number(1000));
	ui->graphInterEdit->setText(QString::number(5000));
    connect(ui->clearBtn, &QPushButton::clicked, this, &MainWindow::onClearGraph);

    // Timer
    timer_ = new QTimer;
    timer_update_ = new QTimer;
  
    // Log file
    file_ = new QFile(QDir::currentPath() + "/log.csv");

    // Get Private bytes from Thread
    data_->moveToThread(thread_);
    thread_->start();
    connect(ui->processIdEdit, &QLineEdit::textChanged, data_, &PlotObject::setProcessId);
    connect(ui->startBtn, &QPushButton::clicked, this, &MainWindow::onStart);
    connect(ui->stopBtn, &QPushButton::clicked, this, &MainWindow::onStop);
    connect(ui->refreshBtn, &QPushButton::clicked, this, &MainWindow::refreshData);
    connect(timer_, &QTimer::timeout, data_, &PlotObject::getProcessStatus);
    connect(timer_update_, &QTimer::timeout, this, &MainWindow::refreshData);
    connect(data_, &PlotObject::sigPrivateBytes, this, &MainWindow::drawData, Qt::QueuedConnection);

    // CustomPlot
    ui->customPlot->addGraph();
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
    dateTicker = QSharedPointer<QCPAxisTickerDateTime>(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("MM-dd hh:mm::ss");
    ui->customPlot->xAxis->setTicker(dateTicker);

    // ComboBox
    ui->comboBox->setModel(listModel_);
    getProcessMap();
    listModel_->setStringList(processList_);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::onSetCurrentProcessId);
    ui->comboBox->setEditable(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawData(Frame frame)
{
    int time = QDateTime::currentSecsSinceEpoch();
    unsigned long data =  frame.private_bytes/1024;

    ui->customPlot->graph(0)->addData(time, data);
    ui->customPlot->graph(0)->rescaleAxes(false);
    int count = ui->customPlot->graph(0)->dataCount();
    ui->statusbar->showMessage("count: " + QString::number(count));

    if (file_->open(QIODevice::ReadWrite | QIODevice::Append))
    {
        QTextStream csv(file_);
        csv << QString(QDateTime::currentDateTime().toString("MM-dd-HH:mm:ss"));
        csv << ",";
        csv << QString::number(data);
        csv << "\n";
        file_->close();
    }
}

void MainWindow::onStart()
{
	if (ui->timeInterEdit->text().isEmpty())
		ui->timeInterEdit->setText(QString::number(1000));
	if (ui->graphInterEdit->text().isEmpty())
		ui->graphInterEdit->setText(QString::number(5000));

	int processRefreshTime = ui->timeInterEdit->text().toInt();
	int graphRefreshTime = ui->timeInterEdit->text().toInt();

	timer_->setInterval(processRefreshTime);
	timer_update_->setInterval(graphRefreshTime);

    if (ui->processIdEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Waring", "Please input/select process name/id");
        return;
    }
    timer_->start();
    timer_update_->start();
}

void MainWindow::onStop()
{
    timer_->stop();
    timer_update_->stop();
}

void MainWindow::refreshData()
{
    ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
}

void MainWindow::getProcessMap()
{
	DWORD aProcesses[1024];
	DWORD cbNeeded;
	DWORD cProcesses;
	unsigned int i;

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
		GetModuleBaseNameW(hProcess, nullptr, buffer, 50);
		CloseHandle(hProcess);
        if (wcslen(buffer) > 4)
        {
			processMap_.insert(QString::fromWCharArray(buffer), (int)processID);
            processList_ << QString::fromWCharArray(buffer);
        }
	}
    processList_.sort(Qt::CaseInsensitive);
}

void MainWindow::onSetCurrentProcessId(QString processName)
{
    qDebug() << processName;
    int id = processMap_.value(processName);
    ui->comboBox->setCurrentText(processName);
    ui->processIdEdit->setText(QString::number(id));
}

void MainWindow::onClearGraph()
{
    ui->customPlot->graph(0)->data().data()->clear();
    this->refreshData();
}
