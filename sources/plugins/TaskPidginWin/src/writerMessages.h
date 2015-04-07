#ifndef __WRITER_MESSAGES_H__
#define __WRITER_MESSAGES_H__

#include "coex.h"

#include <iostream>
#include <QCryptographicHash>
#include <QDateTime>
#include <QDirIterator>
#include <QFile>
#include <QRegExp>
#include <QString>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class writerMessagesPidgin
{
public:
    writerMessagesPidgin(QString fileName, QString messangerName);

    bool opened(
    );

    void writeAccountInfo_field(
        QString field_name,
        QString field_value
    );
    void writeAccountInfo(
        QString name,
        QString email,
        QString protocol,
        QString password);

    void writeContactList(
        QString account,
        QString protocol,
        QString alias,
        QString name);

    void writeMessage(
        QString chathID,
        QString account,
        QString protocol,
        QString author,
        QString dataTime,
        QString message
    );

    ~writerMessagesPidgin();
private:
    QFile *m_pFile;
    QXmlStreamWriter* m_pXmlWriter;
    bool m_bOpened;
};

#endif // __WRITER_MESSAGES_H__
