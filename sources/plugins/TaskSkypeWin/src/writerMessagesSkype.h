#ifndef __WRITER_MESSAGES_SKYPE_H__
#define __WRITER_MESSAGES_SKYPE_H__

#include "coex.h"

#include <QCryptographicHash>
#include <QDateTime>
#include <QFile>
#include <QRegExp>
#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class writerMessagesSkype
{
public:
    writerMessagesSkype(QString fileResult);

    bool opened();

    // like skype
    void writeSkype_field(
        QString field_name,
        QString field_value
    );

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

#endif // __WRITER_MESSAGES_SKYPE_H__
