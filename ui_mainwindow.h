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
#include <QtWidgets/QSpinBox>
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
    QPushButton *refreshProcessBtn;
    QLineEdit *processIdEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *timerInter;
    QLineEdit *timeInterEdit;
    QLabel *graphInter;
    QLineEdit *graphInterEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *countLabel;
    QSpinBox *spinBox;
    QPushButton *startBtn;
    QPushButton *stopBtn;
    QPushButton *refreshGraphBtn;
    QPushButton *clearBtn;
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

        refreshProcessBtn = new QPushButton(centralwidget);
        refreshProcessBtn->setObjectName(QString::fromUtf8("refreshProcessBtn"));

        horizontalLayout->addWidget(refreshProcessBtn);

        processIdEdit = new QLineEdit(centralwidget);
        processIdEdit->setObjectName(QString::fromUtf8("processIdEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(processIdEdit->sizePolicy().hasHeightForWidth());
        processIdEdit->setSizePolicy(sizePolicy);
        processIdEdit->setMinimumSize(QSize(10, 0));
        processIdEdit->setInputMask(QString::fromUtf8(""));
        processIdEdit->setMaxLength(6);

        horizontalLayout->addWidget(processIdEdit);

        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(3, 5);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        timerInter = new QLabel(centralwidget);
        timerInter->setObjectName(QString::fromUtf8("timerInter"));

        horizontalLayout_3->addWidget(timerInter);

        timeInterEdit = new QLineEdit(centralwidget);
        timeInterEdit->setObjectName(QString::fromUtf8("timeInterEdit"));
        timeInterEdit->setInputMask(QString::fromUtf8(""));

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
        countLabel = new QLabel(centralwidget);
        countLabel->setObjectName(QString::fromUtf8("countLabel"));

        horizontalLayout_2->addWidget(countLabel);

        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(999999999);
        spinBox->setSingleStep(100);
        spinBox->setValue(100);

        horizontalLayout_2->addWidget(spinBox);

        startBtn = new QPushButton(centralwidget);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));

        horizontalLayout_2->addWidget(startBtn);

        stopBtn = new QPushButton(centralwidget);
        stopBtn->setObjectName(QString::fromUtf8("stopBtn"));

        horizontalLayout_2->addWidget(stopBtn);

        refreshGraphBtn = new QPushButton(centralwidget);
        refreshGraphBtn->setObjectName(QString::fromUtf8("refreshGraphBtn"));

        horizontalLayout_2->addWidget(refreshGraphBtn);

        clearBtn = new QPushButton(centralwidget);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));

        horizontalLayout_2->addWidget(clearBtn);

        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 2);
        horizontalLayout_2->setStretch(3, 2);
        horizontalLayout_2->setStretch(4, 2);
        horizontalLayout_2->setStretch(5, 2);

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

        refreshProcessBtn->setText(QCoreApplication::translate("MainWindow", "refreshID", nullptr));
        processIdEdit->setText(QString());
        processIdEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\346\255\244\345\244\204\345\277\205\351\241\273\346\234\211PID\345\200\274\357\274\214\350\207\252\345\212\250\345\220\214\346\255\245", nullptr));
        timerInter->setText(QCoreApplication::translate("MainWindow", "processRefreshInterval(ms):", nullptr));
        graphInter->setText(QCoreApplication::translate("MainWindow", "graphRefreshInterval(ms):", nullptr));
        countLabel->setText(QCoreApplication::translate("MainWindow", "bufferNum:", nullptr));
        startBtn->setText(QCoreApplication::translate("MainWindow", "startTimer", nullptr));
        stopBtn->setText(QCoreApplication::translate("MainWindow", "stopTimer", nullptr));
        refreshGraphBtn->setText(QCoreApplication::translate("MainWindow", "refreshGraph", nullptr));
        clearBtn->setText(QCoreApplication::translate("MainWindow", "clearGraph", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
