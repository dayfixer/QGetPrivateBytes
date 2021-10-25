#ifndef PLOTOBJECT_H
#define PLOTOBJECT_H

#include "global.h"
#include <QObject>

class PlotObject : public QObject
{
    Q_OBJECT
public:
    explicit PlotObject(QObject *parent = nullptr);

    void getProcessStatus();
    void setProcessId(QString str);
private:
    unsigned int processId_;
signals:
    void sigPrivateBytes(Frame);
};

#endif // PLOTOBJECT_H
