#include "writerXML.h"
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QCryptographicHash>

writerXML::writerXML()
{
}
writerXML::~writerXML()
{
}
bool writerXML::opened()
{
	return m_bOpened;
}

bool writerFoudnArchive::opened()
{
    return m_bOpened;
}

writerFoudnArchive::writerFoudnArchive(QString fileType)
{
    m_bOpened = true;
    m_pFile= new QFile(fileType);
    if (!m_pFile->open(QIODevice::Append))
    {
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

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "id");
    QString md5Id = QCryptographicHash::hash( (pathWay+archiveType+suffix+size+password+archiveFileList).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeCharacters("archive_"+ md5Id);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "doc_type");
    m_pXmlWriter->writeCharacters("file");
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "application");
    m_pXmlWriter->writeCharacters(archiveType);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "file_suffix");
    m_pXmlWriter->writeCharacters(suffix);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "file_size");
    m_pXmlWriter->writeCharacters(size);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "file_password");
    m_pXmlWriter->writeCharacters(password);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "file_path");
    m_pXmlWriter->writeCharacters(pathWay);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "file_list");
    m_pXmlWriter->writeCharacters(archiveFileList);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeEndElement();
}
