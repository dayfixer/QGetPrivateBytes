#ifndef LOGOBJECT_H
#define LOGOBJECT_H

#include <QFile>
#include <QObject>

class LogObject : public QObject
{
    Q_OBJECT
public:
    explicit LogObject(QObject *parent = nullptr);

    QString getNewdayFile();

    void writeLog(QString);

    bool isANewDay();
private:
    QFile* file_;

    static int today;
signals:

};

#endif // LOGOBJECT_H
