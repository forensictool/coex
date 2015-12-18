#ifndef __TASK_THUNDERBIRD_H__
#define __TASK_THUNDERBIRD_H__

#include "coex.h"

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>

class XMLwriter
{
	public:
		void XMLwriter::write_field(QXmlStreamWriter &xmlWriter, QString sName, QString sValue);
		void XMLwriter::writeFile(QXmlStreamWriter &xmlWriter, int mode, QString name);
		void XMLwriter::writeMessage(QXmlStreamWriter &xmlWriter, QString date, QString from, QString to, QString text);
};

class TaskExample : coex::ITask
{
	public:
		TaskExample();
		virtual QString help();
		virtual QString name();
		virtual QString author();
		virtual QString description();

		virtual bool isSupportOS(const coex::ITypeOperationSystem *os);
		virtual void setOption(QStringList options);
		virtual bool execute(const coex::IConfig *config);

		void TaskExample::openfile(QString input, QXmlStreamWriter *xmlWriter);
		void TaskExample::pars(QString str, QXmlStreamWriter *xmlWriter);
	private:
		bool m_bDebug;
};

extern "C"
{
	coex::ITask* createTask();
}

#endif // __TASK_THUNDERBIRD_H__
