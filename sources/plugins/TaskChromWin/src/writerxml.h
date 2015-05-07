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
/*!
 * \brief The writerXML class
 */
class writerXML : TaskChromWin
{
public:
    writerXML(QString fileName);

    bool opened(
    );
    /*! 
     * \brief writeField
     * \param field_name
     * \param field_value
     */
    void writeField(QString field_name, QString field_value);
    void writePreferences(QString name, QString value, QString owner);
    void writeBookmarks(QString name,QString value, QString title,QString owner,QString date);
    /*!
     * \brief writeHistory
     * \param name
     * \param url
     * \param date
     * \
     */
    void writeHistory(QString name, QString url,QString visit_count,QString date,QString owner);
    void writeHistoryDowload(QString dowload_path, QString dowload_url,QString dowload_referrer,QString dowload_size,QString dowload_time_start,QString dowload_time_end,QString owner);
    void writeHistorySearch(QString term,QString owner);
    void writeExt(QString name,QString owner);
    void writeLogin(QString url,QString login,QString date_created,QString owner);

    ~writerXML();
private:
    QFile *m_pFile;
    QXmlStreamWriter* m_pXmlWriter;
    bool m_bOpened;
};

#endif // __WRITER_MESSAGES_H__
