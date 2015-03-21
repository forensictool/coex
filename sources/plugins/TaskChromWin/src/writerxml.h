#ifndef __WRITER_MESSAGES_H__
#define __WRITER_MESSAGES_H__

#include "coex.h"
#include "taskchromwin.h"

#include <iostream>
#include <QCryptographicHash>
//#include <QDateTime>
//#include <QDirIterator>
#include <QFile>
//#include <QRegExp>
#include <QString>
//#include <QTextStream>
//#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class writerXML : TaskChromWin
{
public:
    writerXML(QString fileName);

    bool opened(
    );

    void writeField(QString field_name,QString field_value);
    void writePreferences(QString name,QString value);
    void writeBookmarks(QString name,QString value, QString title);

    void writeHistory(QString name, QString url,QString date);
    void writeHistoryDowload(QString dowload_path, QString dowload_url,QString dowload_referrer,QString dowload_size,QString dowload_time_start,QString dowload_time_end);
    void writeHistorySearch(QString term);


    ~writerXML();
private:
    QFile *m_pFile;
    QXmlStreamWriter* m_pXmlWriter;
    bool m_bOpened;
};

#endif // __WRITER_MESSAGES_H__
