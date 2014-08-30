#ifndef __SKYPE_WIN_TASK_H__
#define __SKYPE_WIN_TASK_H__

#include "coex.h"

#include <QString>
#include <QFile>
#include <QXmlStreamWriter>

extern "C"
{
	QString getLibName();
	bool execute(const coex::config &);
}

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
    writerMessagesSkype(QString fileResult, QString type, QString messangerName);

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

#endif // __SKYPE_WIN_TASK_H__
