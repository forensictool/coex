#include "xml.h"

bool XMLwriter::opened()
{
    return m_bOpened;
}

XMLwriter::XMLwriter(QString fileName)
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

XMLwriter::~XMLwriter()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}

void XMLwriter::writeField(QString field_name, QString field_value)
{
    if (!field_value.isEmpty())
    {
        m_pXmlWriter->writeStartElement("field");
        m_pXmlWriter->writeAttribute("name", field_name);
        m_pXmlWriter->writeCharacters(field_value);
        m_pXmlWriter->writeEndElement();
    }
}

void XMLwriter::writePasswords(QString url, QString login, QString password)
{
    if (!m_bOpened)return;

    m_pXmlWriter->writeStartElement("doc");

    writeField("url", url);
    writeField("login", login);
    writeField("password", password);

    m_pXmlWriter->writeEndElement();
}