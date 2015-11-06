#ifndef __TASK_OUTLOOK_H__
#define __TASK_OUTLOOK_H__

#include "coex.h"
#include "QByteArray"
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>
#include <iostream>
#include <QDirIterator>
#include <QRegExp>
#include <QTextStream>
#include <QDebug>

class taskOutlook : coex::ITask
{
public:
    void ReadFile();
    QStringList Prov();
    taskOutlook();
    virtual QString help();
    virtual QString name();
    virtual QString author();
    virtual QString description();

    virtual bool isSupportOS(const coex::ITypeOperationSystem *os);
    virtual void setOption(QStringList);
    virtual bool execute(const coex::IConfig *config);
private:
    bool m_bDebug;
    QStringList Prov(QStringList list,QStringList oflist);

};

extern "C"
{
    coex::ITask* createTask();
}

#endif // __TASK_OUTLOOK__
