#include "writerMessages.h"

writerSearchProgram::writerSearchProgram(QString fileName)
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

writerSearchProgram::~writerSearchProgram()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}

bool writerSearchProgram::opened()
{
    return m_bOpened;
}

void writerSearchProgram::writeAccountInfo_field(
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
void writerSearchProgram::writeProgram(
    QString path,
    QString name
)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash( (path).toAscii(), QCryptographicHash::Md5 ).toHex();

    m_pXmlWriter->writeStartElement("doc");

    writeAccountInfo_field("doc_type", "katalog");
    writeAccountInfo_field("id", "katalog_"+ md5Id);
    writeAccountInfo_field("application", "SearchProgram");
    writeAccountInfo_field("path", path);
    writeAccountInfo_field("name", name);

    m_pXmlWriter->writeEndElement();
}
