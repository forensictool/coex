#ifndef __TASK_SYSTEM_LOG_WIN_H__
#define __TASK_SYSTEM_LOG_WIN_H__

#include "coex.h"

#include <QString>
#include <QMap>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <iostream>
#include <QXmlStreamWriter>

class TaskSystemLogWin : coex::ITask
{
	public:
		TaskSystemLogWin();
		virtual QString help();
		virtual QString name();
		virtual QString author();
		virtual QString description();

		virtual bool isSupportOS(const coex::ITypeOperationSystem *os);
		virtual void setOption(QStringList options);
		virtual bool execute(const coex::IConfig *config);
	private:
		bool m_bDebug;
};

extern "C"
{
	coex::ITask* createTask();
}

#endif // __TASK_SYSTEM_LOG_WIN_H__
