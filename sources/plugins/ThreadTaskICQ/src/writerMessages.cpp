#include "writerMessages.h"
#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QCryptographicHash>

bool writerMessagesICQ::opened()
{
    return m_bOpened;
}

writerMessagesICQ::writerMessagesICQ(QString fileName)
{
    m_bOpened = true;
    m_pFile = new QFile(fileName);
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

writerMessagesICQ::~writerMessagesICQ()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}

void writerMessagesICQ::writeAccountInfo_field(
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


void writerMessagesICQ::writeContactList(
        QString emal,
        QString name
)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash( (emal+name).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeStartElement("doc");

    writeAccountInfo_field("doc_type", "contact");
    writeAccountInfo_field("id", "icq_"+ md5Id);
    writeAccountInfo_field("application", "icq");
    writeAccountInfo_field("contact_account", emal);
    writeAccountInfo_field("contact_id", name);

    m_pXmlWriter->writeEndElement();
}

