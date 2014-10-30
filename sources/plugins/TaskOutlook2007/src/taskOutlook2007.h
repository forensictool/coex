#ifndef __TASK_OUTLOOK2007_H__
#define __TASK_OUTLOOK2007_H__

#include "coex.h"
#include "QByteArray"
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>

class taskOutlook2007 : coex::ITask
{
	public:
        void ReadFile();
        taskOutlook2007();
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

#endif // __TASK_OUTLOOK2007__
