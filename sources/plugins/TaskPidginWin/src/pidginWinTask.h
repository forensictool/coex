#ifndef __PIDGIN_WIN_TASK_H__
#define __PIDGIN_WIN_TASK_H__

#include "coex.h"

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>

class TaskPidginWin : coex::ITask
{
	public:
		TaskPidginWin();
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

#endif // __PIDGIN_WIN_TASK_H__
