#ifndef __WRITER_MESSAGES_H__
#define __WRITER_MESSAGES_H__

#include "coex.h"
#include "taskmediascanner.h"

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

class XMLwriter : TaskMediaScanner
{
public:
    void write_field(QXmlStreamWriter &xmlWriter,QString sName,QString sValue);
    void writeMedia(QString path,QXmlStreamWriter &xmlWriter,int mode,QString id,QString datecreate,QString datemodify,QString type,bool meta);
};
#endif // __WRITER_MESSAGES_H__
