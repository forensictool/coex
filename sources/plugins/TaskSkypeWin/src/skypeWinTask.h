#ifndef __SKYPE_WIN_TASK_H__
#define __SKYPE_WIN_TASK_H__

#include "coex.h"

#include <QString>
#include <QFile>
#include <QXmlStreamWriter>


class TaskSkypeWin : coex::ITask
{
	public:
		TaskSkypeWin();
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

#endif // __SKYPE_WIN_TASK_H__
