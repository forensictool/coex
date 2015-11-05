#ifndef __TASK_MEDIA_H__
#define __TASK_MEDIA_H__

#include "coex.h"

#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QFileInfo>
#include <QDateTime>
#include <QCryptographicHash>
#include <QDir>
#include <QDirIterator>
#include <QStringList>


class TaskMediaScanner : coex::ITask
{
	public:
		TaskMediaScanner();
		virtual QString help();
		virtual QString name();
		virtual QString author();
		virtual QString description();

		virtual bool isSupportOS(const coex::ITypeOperationSystem *os);
		virtual void setOption(QStringList options);
		virtual bool execute(const coex::IConfig *config);
        void read_id3(QFile &file, QXmlStreamWriter &xmlWriter);
        void read_jfif(QFile &file, QXmlStreamWriter &xmlWriter);
        void read_riff(QFile &file, QXmlStreamWriter &xmlWriter);
        void scan_media(QString medianame, QXmlStreamWriter *xmlWriter);
	private:
		bool m_bDebug;
};

extern "C"
{
	coex::ITask* createTask();
}

#endif // __TASK_MEDIA_H__
