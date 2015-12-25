#include "xml.h"

/*XMLwriter::writeLine(QString id, QString content)
        {
            if (!m_bOpened)return;
            m_pXmlWriter->writeStartElement("line");
            writeField(xmlWriter, id);
            writeField(xmlWriter, content);
            m_pXmlWriter->writeEndElement();
        }
        */
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


bool XMLwriter::opened()
{
    return m_bOpened;
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


XMLwriter::~XMLwriter()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}
