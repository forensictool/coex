#ifndef __TASK_MEDIA_H__
#define __TASK_MEDIA_H__

#include "coex.h"

#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QXmlStreamWriter>

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
        void readId3(QFile &file, QXmlStreamWriter &xmlWriter);
        void readJfif(QFile &file, QXmlStreamWriter &xmlWriter);
        void readRiff(QFile &file, QXmlStreamWriter &xmlWriter);
        void scanMedia(QString medianame, QXmlStreamWriter *xmlWriter);
        void writeField(QXmlStreamWriter &xmlWriter,QString sName,QString sValue);
        void writeMedia(QString path,QXmlStreamWriter &xmlWriter,int mode,QString id,QString datecreate,QString datemodify,QString type,bool meta);
	private:
		bool m_bDebug;
};

extern "C"
{
	coex::ITask* createTask();
}

#endif // __TASK_MEDIA_H__
