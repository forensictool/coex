#ifndef __WRITER_MESSAGES_H__
#define __WRITER_MESSAGES_H__

#include "coex.h"

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>

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


class writerMessagesSkype : writerMessages
{
public:
    writerMessagesSkype(QString fileResult);

    bool opened(
    );

    // like skype
    void writeMessage(
        QString author,
        QString timestamp,
        QString body_xml
    );

    void writeCalls(
        QString begin_timestamp,
        QString duration,
        QString host_identity,
        QString current_video_audience
    );


    // like skype contact
    void writeContacts(
        QString skypename ,
        QString fullName,
        QString birthday,
        QString gender,
        QString phone_mobile,
        QString languages,
        QString country,
        QString city
    );

    // like skype info account
    void writeInfo(
        QString skypeName,
        QString fullName,
        QString emails,
        QString ipcountry
    );
    ~writerMessagesSkype();
private:
    QFile *m_pFile;
    QXmlStreamWriter* m_pXmlWriter;
    //QXmlStreamWriter* m_pXmlWriter;
    bool m_bOpened;
};

#endif // __WRITER_MESSAGES_H__
