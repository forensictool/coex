#ifndef __PIDGIN_WIN_TASK_H__
#define __PIDGIN_WIN_TASK_H__

#include "../../../apps/coex/src/coex/coex.h"

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>

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

class writerMessagesPidgin : writerMessages
{
public:
    writerMessagesPidgin(QString fileName, QString messangerName);

    bool opened(
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

    void writeInfoLog(
        QString chathID,
        QString account,
        QString data,
        QString protocol
    );

    void writeMessage(
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

#endif // __PIDGIN_WIN_TASK_H__