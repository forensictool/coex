#ifndef __TASK_WINREG_H__
#define __TASK_WINREG_H__

#include "coex.h"
#include "QByteArray"
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>

class taskWinReg : coex::ITask
{
	public:
        void ReadFile();
        taskWinReg();
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

#endif
