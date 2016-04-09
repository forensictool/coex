#ifndef __WRITER_MESSAGES_H__
#define __WRITER_MESSAGES_H__

#include "coex.h"
#include "threadTaskICQ.h"

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>

class writerMessagesICQ : ThreadTaskICQ
{
public:
    writerMessagesICQ(QString fileName);

    bool opened(
    );

    void writeAccountInfo_field(
        QString field_name,
        QString field_value
    );

    void writeContactList(
        QString emal,
        QString name);

    ~writerMessagesICQ();
private:
    QFile *m_pFile;
    QXmlStreamWriter* m_pXmlWriter;
    bool m_bOpened;
};

#endif // __WRITER_MESSAGES_H__
