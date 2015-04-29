#ifndef __WRITER_MESSAGES_H__
#define __WRITER_MESSAGES_H__

#include "coex.h"

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>

/*!
 * \brief The writerMessages class
 */
class writerMessages
{
public:
    writerMessages();

    bool opened();

      //about pidgin log file
     void writeInfo();

    //like pidgin
    void writeMessage();
    ~writerMessages();
private:
    bool m_bOpened;
};

/*!
 * \brief The writerMessagesPidgin class
 */
class writerMessagesPidgin : writerMessages
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
        QString emal,
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
