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
void writerXML::writePreferences(QString name,QString value)
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

void writerXML::writeBookmarks(QString name, QString value,QString title)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash((value + name).toAscii(), QCryptographicHash::Md5).toHex();

    m_pXmlWriter->writeStartElement("doc");
    writeField("doc_type", "bookmarks");
    writeField("id", "chrome_" + md5Id);
    writeField("application", "chrome");
    writeField("bookmarks_param_name", name);
    writeField("bookmarks_param_title", title);
    writeField("bookmarks_param_value", value);

    m_pXmlWriter->writeEndElement();

}

void writerXML::writeHistory(QString name, QString url, QString date)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash((name + url + date).toAscii(), QCryptographicHash::Md5).toHex();

    m_pXmlWriter->writeStartElement("doc");
    writeField("doc_type", "history");
    writeField("id", "chrome_" + md5Id);
    writeField("application", "chrome");
    writeField("bookmarks_param_name", name);
    writeField("bookmarks_param_url", url);
    writeField("bookmarks_param_date", date);

    m_pXmlWriter->writeEndElement();
}

void writerXML::writeHistoryDowload(QString dowload_path, QString dowload_url,QString dowload_referrer,QString dowload_size,QString dowload_time_start,QString dowload_time_end)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash(("download" + dowload_url + dowload_time_start + "Chrome").toAscii(), QCryptographicHash::Md5).toHex();

    m_pXmlWriter->writeStartElement("doc");
    writeField("doc_type", "history");
    writeField("id", "chrome_" + md5Id);
    writeField("application", "chrome");
    writeField("bookmarks_param_path", dowload_path);
    writeField("bookmarks_param_url", dowload_url);
    writeField("bookmarks_param_referrer", dowload_referrer);
    writeField("bookmarks_param_size", dowload_size);
    writeField("bookmarks_param_time_start", dowload_time_start);
    writeField("bookmarks_param_time_end", dowload_time_end);

    m_pXmlWriter->writeEndElement();


}

void writerXML::writeHistorySearch(QString term)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash((term + "Chrome").toAscii(), QCryptographicHash::Md5).toHex();

    m_pXmlWriter->writeStartElement("doc");
    writeField("doc_type", "history");
    writeField("id", "chrome_" + md5Id);
    writeField("application", "chrome");
    writeField("bookmarks_param_term", term);

    m_pXmlWriter->writeEndElement();


}

