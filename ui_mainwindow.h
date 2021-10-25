/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLineEdit *processIdEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *timerInter;
    QLineEdit *timeInterEdit;
    QLabel *graphInter;
    QLineEdit *graphInterEdit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *startBtn;
    QPushButton *stopBtn;
    QPushButton *refreshBtn;
    QCustomPlot *customPlot;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        processIdEdit = new QLineEdit(centralwidget);
        processIdEdit->setObjectName(QString::fromUtf8("processIdEdit"));

        horizontalLayout->addWidget(processIdEdit);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(2, 4);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        timerInter = new QLabel(centralwidget);
        timerInter->setObjectName(QString::fromUtf8("timerInter"));

        horizontalLayout_3->addWidget(timerInter);

        timeInterEdit = new QLineEdit(centralwidget);
        timeInterEdit->setObjectName(QString::fromUtf8("timeInterEdit"));

        horizontalLayout_3->addWidget(timeInterEdit);

        graphInter = new QLabel(centralwidget);
        graphInter->setObjectName(QString::fromUtf8("graphInter"));

        horizontalLayout_3->addWidget(graphInter);

        graphInterEdit = new QLineEdit(centralwidget);
        graphInterEdit->setObjectName(QString::fromUtf8("graphInterEdit"));

        horizontalLayout_3->addWidget(graphInterEdit);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        startBtn = new QPushButton(centralwidget);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));

        horizontalLayout_2->addWidget(startBtn);

        stopBtn = new QPushButton(centralwidget);
        stopBtn->setObjectName(QString::fromUtf8("stopBtn"));

        horizontalLayout_2->addWidget(stopBtn);

        refreshBtn = new QPushButton(centralwidget);
        refreshBtn->setObjectName(QString::fromUtf8("refreshBtn"));

        horizontalLayout_2->addWidget(refreshBtn);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        customPlot = new QCustomPlot(centralwidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));

        gridLayout->addWidget(customPlot, 3, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 1);
        gridLayout->setRowStretch(3, 7);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "getPrivateBytes", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "processID:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "111", nullptr));

        processIdEdit->setText(QString());
        timerInter->setText(QCoreApplication::translate("MainWindow", "processRefreshInterval(ms):", nullptr));
        graphInter->setText(QCoreApplication::translate("MainWindow", "graphRefreshInterval(ms):", nullptr));
        startBtn->setText(QCoreApplication::translate("MainWindow", "startTimer", nullptr));
        stopBtn->setText(QCoreApplication::translate("MainWindow", "stopTimer", nullptr));
        refreshBtn->setText(QCoreApplication::translate("MainWindow", "refreshGraph", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
