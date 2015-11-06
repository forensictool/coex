#ifndef __WRITER_ADDRESS_H__
#define __WRITER_ADDRESS_H__

#include "coex.h"
#include <QDateTime>
#include <QDirIterator>
#include <QFile>
#include <QRegExp>
#include <QString>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class writerAddressOutlook
{
public:
    writerAddressOutlook(QString fileName, QString AddressName);

    bool opened();
    void writeMessage(
        QString author,
        QString dataTime,
        QString message,
        QString Theme
    );


    ~writerAddressOutlook();
private:
    QFile *m_pFile;
    QXmlStreamWriter* m_pXmlWriter;
    bool m_bOpened;
};

#endif // __WRITER_ADDRES_H__
