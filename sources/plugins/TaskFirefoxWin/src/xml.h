#ifndef __XML_H__
#define __XML_H__

#include "coex.h"
#include "taskFirefox.h"
#include <QDateTime>
#include <QDirIterator>
#include <QFile>
#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class XMLwriter
{
    public:

        XMLwriter(const QString fileName);

        void writeField(QString field_name, QString field_value);
        bool opened();
        void writeLine(QString id, QString content);
        void writePasswords(QString url, QString login, QString password);

        ~XMLwriter();

    private:
        QFile *m_pFile;
        QXmlStreamWriter* m_pXmlWriter;
        bool m_bOpened;
};

#endif // __XML_H__
