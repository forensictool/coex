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
    write_field(QString field_name, QString field_value);
    writeFile(QString fileName);

    bool opened();
    void writeLine(QString id, QString content);


    ~writeFile();
private:
    QFile *m_pFile;
    QXmlStreamWriter* m_pXmlWriter;
    bool m_bOpened;
};

#endif // __XML_H__
