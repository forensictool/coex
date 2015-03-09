#include "writerxml.h"

bool writerXML::opened()
{
    return m_bOpened;
}

writerXML::writerXML(QString fileName)
{
    m_bOpened = true;
    m_pFile = new QFile(fileName);
    qDebug()<<"efewfwef" << fileName;
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

writerXML::~writerXML()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}

void writerXML::writeField(
    QString field_name,
    QString field_value
)
{
    if (!field_value.isEmpty()) {
        m_pXmlWriter->writeStartElement("field");
        m_pXmlWriter->writeAttribute("name", field_name);
        m_pXmlWriter->writeCharacters(field_value);
        m_pXmlWriter->writeEndElement();
    }
}
void writerXML::writePreferences(
    QString name,
    QString value
)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash((value + name).toAscii(), QCryptographicHash::Md5).toHex();

    m_pXmlWriter->writeStartElement("doc");
    writeField("doc_type", "preference");
    writeField("id", "pidgin_" + md5Id);
    writeField("application", "chrome");
    writeField("preferences_param_name", name);
    writeField("preferences_param_value", value);

    m_pXmlWriter->writeEndElement();
}
