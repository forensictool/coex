#include "writerMessages.h"

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
    m_pXmlWriter->writeStartElement("Messages ");
    m_pXmlWriter->writeAttribute("Messenger" ,messangerName);
}

writerMessagesPidgin::~writerMessagesPidgin()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}

bool writerMessagesPidgin::opened()
{
    return m_bOpened;
}

void writerMessagesPidgin::writeAccountInfo(
    QString name,
    QString email,
    QString protocol,
    QString password
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("info_account");
    m_pXmlWriter->writeAttribute("name", name);
    m_pXmlWriter->writeAttribute("email", email);
    m_pXmlWriter->writeAttribute("password", password);
    m_pXmlWriter->writeAttribute("protocol", protocol);
    m_pXmlWriter->writeEndElement();
}

void writerMessagesPidgin::writeContactList(
    QString account,
    QString protocol,
    QString alias,
    QString name
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("Contact_list");
    m_pXmlWriter->writeAttribute("account", account);
    m_pXmlWriter->writeAttribute("protocol", protocol);
    m_pXmlWriter->writeAttribute("name", alias);
    m_pXmlWriter->writeAttribute("emails", name);
    m_pXmlWriter->writeEndElement();
}

void writerMessagesPidgin::writeInfoLog(
    QString chathID,
    QString account,
    QString data,
    QString protocol
)
{
    if (!m_bOpened) return;
    m_pXmlWriter->writeStartElement("info");
    m_pXmlWriter->writeAttribute("chathID", chathID);
    m_pXmlWriter->writeAttribute("account", account);
    m_pXmlWriter->writeAttribute("data", data);
    m_pXmlWriter->writeAttribute("protocol", protocol);
    m_pXmlWriter->writeEndElement();
}

void writerMessagesPidgin::writeMessage(
    QString author,
    QString dataTime,
    QString message
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("message");
    m_pXmlWriter->writeAttribute("author", author);
    m_pXmlWriter->writeAttribute("dataTime", dataTime);
    m_pXmlWriter->writeAttribute("message", message);
    m_pXmlWriter->writeEndElement();
}