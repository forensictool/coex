
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

//about account.xml file
void writerMessagesPidgin::writeAccountInfo(
    QString name,
    QString email,
    QString protocol,
    QString password
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("doc");

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "id");
    QString md5Id = QCryptographicHash::hash( (protocol+name+password).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeCharacters("pidgin_"+ md5Id);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "doc_type");
    m_pXmlWriter->writeCharacters("account");
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "application");
    m_pXmlWriter->writeCharacters("pidgin");
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "account_id");
    m_pXmlWriter->writeCharacters(name);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "account_mail");
    m_pXmlWriter->writeCharacters(email);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "account_protocol");
    m_pXmlWriter->writeCharacters(protocol);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "account_password");
    m_pXmlWriter->writeCharacters(password);
    m_pXmlWriter->writeEndElement();

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

    m_pXmlWriter->writeStartElement("doc");

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "id");
    QString md5Id = QCryptographicHash::hash( (protocol+account+name).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeCharacters("pidgin_"+ md5Id);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "doc_type");
    m_pXmlWriter->writeCharacters("contact");
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "application");
    m_pXmlWriter->writeCharacters("pidgin");
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "contact_name");
    m_pXmlWriter->writeCharacters(alias);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "contact_account");
    m_pXmlWriter->writeCharacters(account);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "contact_protocol");
    m_pXmlWriter->writeCharacters(protocol);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "contact_id");
    m_pXmlWriter->writeCharacters(name);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeEndElement();
}

//about log file
void writerMessagesPidgin::writeInfoLog(
    QString chathID,
    QString account,
    QString data,
    QString protocol
)
{
    if (!m_bOpened) return;

    m_pXmlWriter->writeStartElement("doc");

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "id");
    QString md5Id = QCryptographicHash::hash( (protocol+account+data).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeCharacters("pidgin_"+ md5Id);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "doc_type");
    m_pXmlWriter->writeCharacters("message");
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "application");
    m_pXmlWriter->writeCharacters("pidgin");
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "message_chat_id");
    m_pXmlWriter->writeCharacters(chathID);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "message_account");
    m_pXmlWriter->writeCharacters(account);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "message_protocol");
    m_pXmlWriter->writeCharacters(protocol);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "message_text");
    m_pXmlWriter->writeCharacters(data);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeEndElement();

}

//like pidgin
void writerMessagesPidgin::writeMessage(
    QString author,
    QString dataTime,
    QString message
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("doc");

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "id");
    QString md5Id = QCryptographicHash::hash( (author+dataTime+message).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeCharacters("pidgin_"+ md5Id);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "doc_type");
    m_pXmlWriter->writeCharacters("message");
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "application");
    m_pXmlWriter->writeCharacters("pidgin");
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "message_author");
    m_pXmlWriter->writeCharacters(author);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "message_dataTime");
    m_pXmlWriter->writeCharacters(dataTime);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "message_message");
    m_pXmlWriter->writeCharacters(message.trimmed());
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeEndElement();
}
