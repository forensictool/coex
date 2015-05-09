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

class writerSearchProgram
{
public:
    writerSearchProgram(QString fileName);

    bool opened(
    );

    void writeAccountInfo_field(
        QString field_name,
        QString field_value
    );
    void writeProgram(QString path, QString name);
    ~writerSearchProgram();
private:
    QFile *m_pFile;
    QXmlStreamWriter* m_pXmlWriter;
    bool m_bOpened;
};

#endif // __WRITER_MESSAGES_H__
