#ifndef __PIDGIN_WIN_TASK_H__
#define __PIDGIN_WIN_TASK_H__

#include "coex.h"

#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>
#include <QDirIterator>
#include <QFile>
#include <QRegExp>
#include <QString>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

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
        void processingContactListPidgin(
                QString inputFile,
                QString outPath
        );
        void processingAccountPidgin(
                QString inputFile,
                QString outPath
        );
        void processingLogPidgin(
                QFileInfo  fileInfo,
                QString outputPath
        );
	private:
		bool m_bDebug;
};

extern "C"
{
	coex::ITask* createTask();
}

#endif // __PIDGIN_WIN_TASK_H__
