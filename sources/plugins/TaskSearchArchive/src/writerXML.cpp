#include "writerXML.h"
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QCryptographicHash>

bool writerFoudnArchive::opened()
{
    return m_bOpened;
}

writerFoudnArchive::writerFoudnArchive(QString fileType)
{
    m_bOpened = true;
    m_pFile = new QFile(fileType);
    if (!m_pFile->open(QIODevice::Append)) {
        m_bOpened = false;
        return;
    }

    m_pXmlWriter = new QXmlStreamWriter();
    m_pXmlWriter->setDevice(m_pFile);

    m_pXmlWriter->setAutoFormatting(true);
    m_pXmlWriter->writeStartDocument();
    m_pXmlWriter->writeStartElement("add");
}

writerFoudnArchive::~writerFoudnArchive()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}

void writerFoudnArchive::writerFoudnArchive_field(
    QString field_name,
    QString field_value
)
{
    if(!field_value.isEmpty())
    {
        m_pXmlWriter->writeStartElement("field");
        m_pXmlWriter->writeAttribute("name", field_name);
        m_pXmlWriter->writeCharacters(field_value);
        m_pXmlWriter->writeEndElement();
    }
}

//about account.xml file
void writerFoudnArchive::writeFound(
    QString pathWay,
    QString archiveType,
    QString suffix,
    QString size,
    QString password,
    QString archiveFileList
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("doc");

    QString md5Id = QCryptographicHash::hash((suffix + size + password + pathWay + archiveFileList + archiveFileList).toAscii(), QCryptographicHash::Md5).toHex();
    writerFoudnArchive_field("doc_type", "file");
    writerFoudnArchive_field("id", "archive_"+ md5Id);
    writerFoudnArchive_field("application", "archive");
    writerFoudnArchive_field("file_type", archiveType);
    writerFoudnArchive_field("file_suffix", suffix);
    writerFoudnArchive_field("file_size", size);
    writerFoudnArchive_field("file_password", password);
    writerFoudnArchive_field("file_path", pathWay);
    writerFoudnArchive_field("file_list", archiveFileList);


    m_pXmlWriter->writeEndElement();
}
