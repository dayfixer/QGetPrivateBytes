#include "plotobject.h"

#include <Windows.h>
#include <Psapi.h>
#include <QDebug>

PlotObject::PlotObject(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<Frame>("Frame");
}

void PlotObject::getProcessStatus()
{
    HANDLE hProcess;
    PROCESS_MEMORY_COUNTERS_EX pmc;

    // Print information about the memory usage of the process.

    DWORD processID = this->processId_;
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |PROCESS_VM_READ, FALSE, processID);
    if (NULL == hProcess)
        return;

    if (GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc)))
    {
        Frame f;
        f.private_bytes = pmc.PrivateUsage;
        emit sigPrivateBytes(f);
    }
    CloseHandle(hProcess);
}

void PlotObject::setProcessId(QString str)
{
    this->processId_ = str.toULong();
}
