#include "logobject.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QTextStream>

int LogObject::today = 0;

LogObject::LogObject(QObject *parent) : QObject(parent)
{

}

QString LogObject::getNewdayFile()
{
    QDateTime datetime = QDateTime::currentDateTime();
    QString timestrFolder = datetime.toString("yyyy-MM");
    QString timestrFile = datetime.toString("yyyy-MM-dd");
    QString dir_str = QCoreApplication::applicationDirPath() + "/csv/" + timestrFolder;

    QDir dir;
    bool res;
    if (!dir.exists(dir_str))
    {
         res = dir.mkpath(dir_str);
    }

    QString fileName = dir_str + "/" + timestrFile + ".csv";
    if (fileName.isEmpty() || res == false)
        return "logError.csv";
    return fileName;
}

void LogObject::writeLog(QString info)
{
    if (isANewDay())
    {
        file_ = new QFile(getNewdayFile());
    }
    if (file_->open(QIODevice::ReadWrite | QIODevice::Append))
    {
        QTextStream csv(file_);
        csv << info;
        file_->close();
    }
}

bool LogObject::isANewDay()
{
    QDateTime datetime = QDateTime::currentDateTime();
    int timeDay = datetime.toString("dd").toInt();
    if (timeDay != LogObject::today)
    {
        LogObject::today = timeDay;
        return true;
    }
    else
    {
        return false;
    }

}

