
#include "writerXML.h"

#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QDebug>

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

writerFoudnArchive::writerFoudnArchive(QString fileName, QString messangerName)
{
    m_bOpened = true;
    m_pFile = new QFile(fileName);
    if (!m_pFile->open(QIODevice::Append))
    {
        std::cout << "Cant open file  failed task\n";
        m_bOpened = false;
        return;
    }
    m_pXmlWriter = new QXmlStreamWriter();
    m_pXmlWriter->setDevice(m_pFile);
    qDebug() << "constructor start";
    m_pXmlWriter->setAutoFormatting(true);
    m_pXmlWriter->writeStartDocument();
    m_pXmlWriter->writeStartElement("Archive ");
    m_pXmlWriter->writeAttribute("Found" ,messangerName);
}

writerFoudnArchive::~writerFoudnArchive()
{
    qDebug() << "constructor finish";
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
    QString password
)
{
    if (!m_bOpened)return;
    qDebug() << "in progress";
    m_pXmlWriter->writeStartElement("info_archive");
    m_pXmlWriter->writeAttribute("pathWay", pathWay);
    m_pXmlWriter->writeAttribute("archiveType", archiveType);
    m_pXmlWriter->writeAttribute("suffix", suffix);
    m_pXmlWriter->writeAttribute("size", size);
    m_pXmlWriter->writeAttribute("password", password);
    m_pXmlWriter->writeEndElement();
}
