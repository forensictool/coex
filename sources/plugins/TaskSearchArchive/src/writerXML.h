#ifndef __WRITER_XML_H__
#define __WRITER_XML_H__

#include "coex.h"

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>

class writerXML
{
public:
    writerXML();

    bool opened();
    void writeInfo();
    void writeMessage();

    ~writerXML();
private:
    bool m_bOpened;
};

class writerFoudnArchive : writerXML
{
public:
    writerFoudnArchive(QString fileType);

    bool opened(
    );

    void writerFoudnArchive_field(
        QString field_name,
        QString field_value
    );

    void writeFound(
        QString pathWay,
        QString archiveType,
        QString suffix,
        QString size,
        QString password,
        QString archiveFileList);

    ~writerFoudnArchive();
private:
    QFile *m_pFile;
    QXmlStreamWriter* m_pXmlWriter;
    bool m_bOpened;
};

#endif // __WRITER_MESSAGES_H__
