#ifndef __TASK_PARSEHDD_H__
#define __TASK_PARSEHDD_H__

#include "coex.h"
#include <iostream>
#include <QFileInfo>
#include <QDirIterator>
#include <QDebug>
#include <QList>
#include <QStringList>
#include <QDir>
#include <QFileInfoList>

class TaskParseHDD : coex::ITask
{
	public:
        TaskParseHDD();
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

#endif // __TASK_S__
