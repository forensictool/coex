
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

writerMessages::writerMessages()
{
}
writerMessages::~writerMessages()
{
}
bool writerMessages::opened()
{
    return m_bOpened;
}

bool writerMessagesPidgin::opened()
{
    return m_bOpened;
}

writerMessagesPidgin::writerMessagesPidgin(QString fileName, QString messangerName)
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

    //m_pXmlWriter->writeAttribute("Messenger" ,messangerName);
}

writerMessagesPidgin::~writerMessagesPidgin()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}

void writerMessagesPidgin::writeAccountInfo_field(
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
void writerMessagesPidgin::writeAccountInfo(
    QString name,
    QString email,
    QString protocol,
    QString password
)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash( (email+protocol+name+password).toAscii(), QCryptographicHash::Md5 ).toHex();

    m_pXmlWriter->writeStartElement("doc");

    writeAccountInfo_field("doc_type", "account");
    writeAccountInfo_field("id", "pidgin_"+ md5Id);
    writeAccountInfo_field("application", "pidgin");
    writeAccountInfo_field("account_id", name);
    writeAccountInfo_field("account_mail", email);
    writeAccountInfo_field("account_protocol", protocol);
    writeAccountInfo_field("account_password", password);

    m_pXmlWriter->writeEndElement();
}

//about contacts.xml file
void writerMessagesPidgin::writeContactList(
    QString account,
    QString protocol,
    QString alias,
    QString name
)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash( (protocol+account+name+alias).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeStartElement("doc");

    writeAccountInfo_field("doc_type", "contact");
    writeAccountInfo_field("id", "pidgin_"+ md5Id);
    writeAccountInfo_field("application", "pidgin");
    writeAccountInfo_field("contact_name", alias);
    writeAccountInfo_field("contact_account", account);
    writeAccountInfo_field("contact_protocol", protocol);
    writeAccountInfo_field("contact_id", name);

    m_pXmlWriter->writeEndElement();
}



void writerMessagesPidgin::writeMessage(
    QString chathID,
    QString account,
    QString protocol,
    QString author,
    QString dataTime,
    QString message
)
{
    if (!m_bOpened)return;
    QString md5Id = QCryptographicHash::hash((chatID+account+protocol+author,dataTime,message).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeStartElement("doc");

    writeAccountInfo_field("doc_type", "message");
    writeAccountInfo_field("id", "pidgin_"+ md5Id);
    writeAccountInfo_field("application", "pidgin");
    writeAccountInfo_field("message_chat_id", chathID);
    writeAccountInfo_field("message_account", account);
    writeAccountInfo_field("message_protocol", protocol);
    writeAccountInfo_field("message_author", author);
    writeAccountInfo_field("message_dataTime", dataTime);
    writeAccountInfo_field("message_message", message);

    m_pXmlWriter->writeEndElement();
}
