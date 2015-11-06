#include "writerAddress.h"

writerAddressOutlook::writerAddressOutlook(QString fileName, QString AddressName)
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
    m_pXmlWriter->writeStartElement("Addres ");
    m_pXmlWriter->writeAttribute("Addres" ,AddressName);
}

writerAddressOutlook::~writerAddressOutlook()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}

bool writerAddressOutlook::opened()
{
    return m_bOpened;
}



void writerAddressOutlook::writeMessage(
    QString author,
    QString dataTime,
    QString message,
    QString Theme
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("message");
    m_pXmlWriter->writeAttribute("author", author);
    m_pXmlWriter->writeAttribute("dataTime", dataTime);
    m_pXmlWriter->writeAttribute("Theme",Theme);
    m_pXmlWriter->writeAttribute("message", message);
    m_pXmlWriter->writeEndElement();
}
