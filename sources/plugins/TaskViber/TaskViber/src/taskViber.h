#ifndef __TASK_Viber_H__
#define __TASK_Viber_H__

#include "coex.h"

#include <QString>
#include <QFile>
#include <QDateTime>
#include <QtSql>
#include <iomanip>
#include <iostream>
#include <QDirIterator>
#include <QRegExp>
#include <QTextStream>
#include <QDir>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QCoreApplication>
#include <fstream>
#include <QDebug>
#include <sys/types.h>
#include <QUrl>

class TaskViber : coex::ITask
{
    public:
        TaskViber();
        virtual QString help();
        virtual QString name();
        virtual QString author();
        virtual QString description();

        virtual bool isSupportOS(const coex::ITypeOperationSystem *os);
        virtual void setOption(QStringList);
        virtual bool execute(const coex::IConfig *config);

    private:
        bool m_bDebug;
};

extern "C"
{
    coex::ITask* createTask();
}

#endif // __TASK_Viber__
