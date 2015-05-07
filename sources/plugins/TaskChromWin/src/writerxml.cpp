#include "writerxml.h"

bool writerXML::opened()
{
    return m_bOpened;
}

/*!
 * \brief writerXML::writerXML
 * \param fileName
 */

writerXML::writerXML(QString fileName)
{
    m_bOpened = true;
    m_pFile = new QFile(fileName);
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

void writerXML::writeField(QString field_name, QString field_value)
{
    if (!field_value.isEmpty())
    {
        m_pXmlWriter->writeStartElement("field");
        m_pXmlWriter->writeAttribute("name", field_name);
        m_pXmlWriter->writeCharacters(field_value);
        m_pXmlWriter->writeEndElement();
    }
}

/*!
 * \brief writerXML::writePreferences
 * \param name
 * \param value
 * \param owner
 */

void writerXML::writePreferences(QString name, QString value, QString owner)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash((value + name).toAscii(), QCryptographicHash::Md5).toHex();

    m_pXmlWriter->writeStartElement("doc");
    writeField("doc_type", "preferences");
    writeField("id", "chrome_" + md5Id);
    writeField("application", "chrome");
    writeField("owner", owner);
    writeField("preferences_param_name", name);
    writeField("preferences_param_value", value);


    m_pXmlWriter->writeEndElement();
}

/*!
 * \brief writerXML::writeBookmarks
 * \param name
 * \param value
 * \param title
 * \param owner
 * \param date
 */

void writerXML::writeBookmarks(QString name, QString value, QString title, QString owner, QString date)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash((value + name).toAscii(), QCryptographicHash::Md5).toHex();

    m_pXmlWriter->writeStartElement("doc");
    writeField("doc_type", "bookmarks");
    writeField("id", "chrome_" + md5Id);
    writeField("application", "chrome");
    writeField("owner", owner);
    writeField("bookmarks_param_date_added", date);
    writeField("bookmarks_param_name", name);
    writeField("bookmarks_param_value", value);
    writeField("bookmarks_param_title", title);

    m_pXmlWriter->writeEndElement();
}

/*!
 * \brief writerXML::writeHistory
 * \param name
 * \param url
 * \param visit_count
 * \param date
 * \param owner
 */

void writerXML::writeHistory(QString name, QString url, QString visit_count, QString date, QString owner)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash((name + url + date).toAscii(), QCryptographicHash::Md5).toHex();

    m_pXmlWriter->writeStartElement("doc");
    writeField("doc_type", "history");
    writeField("id", "chrome_" + md5Id);
    writeField("application", "chrome");
    writeField("owner", owner);
    writeField("history_param_name", name);
    writeField("history_param_url", url);
    writeField("history_param_visit_count", visit_count);
    writeField("history_param_last_visit", date);

    m_pXmlWriter->writeEndElement();
}

/*!
 * \brief writerXML::writeHistoryDowload
 * \param dowload_path
 * \param dowload_url
 * \param dowload_referrer
 * \param dowload_size
 * \param dowload_time_start
 * \param dowload_time_end
 * \param owner
 */

void writerXML::writeHistoryDowload(QString dowload_path, QString dowload_url, QString dowload_referrer, QString dowload_size, QString dowload_time_start, QString dowload_time_end, QString owner)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash(("download" + dowload_url + dowload_time_start + "Chrome").toAscii(), QCryptographicHash::Md5).toHex();

    m_pXmlWriter->writeStartElement("doc");
    writeField("doc_type", "download");
    writeField("id", "chrome_" + md5Id);
    writeField("application", "chrome");
    writeField("owner", owner);
    writeField("download_param_path", dowload_path);
    writeField("download_param_url", dowload_url);
    writeField("download_param_referrer", dowload_referrer);
    writeField("download_param_size", dowload_size);
    writeField("download_param_time_start", dowload_time_start);
    writeField("download_param_time_end", dowload_time_end);

    m_pXmlWriter->writeEndElement();
}

/*!
 * \brief writerXML::writeHistorySearch
 * \param term
 * \param owner
 */

void writerXML::writeHistorySearch(QString term, QString owner)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash((term + "Chrome").toAscii(), QCryptographicHash::Md5).toHex();

    m_pXmlWriter->writeStartElement("doc");
    writeField("doc_type", "search");
    writeField("id", "chrome_" + md5Id);
    writeField("application", "chrome");
    writeField("owner", owner);
    writeField("search_param_term", term);

    m_pXmlWriter->writeEndElement();
}

/*!
 * \brief writerXML::writeExt
 * \param name
 * \param owner
 */

void writerXML::writeExt(QString name, QString owner)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash((name + "Chrome").toAscii(), QCryptographicHash::Md5).toHex();

    m_pXmlWriter->writeStartElement("doc");
    writeField("doc_type", "extension");
    writeField("id", "chrome_" + md5Id);
    writeField("application", "chrome");
    writeField("extension_param_owner", owner);
    writeField("extension_param_name",name);

    m_pXmlWriter->writeEndElement();
}

/*!
 * \brief writerXML::writeLogin
 * \param url
 * \param login
 * \param owner
 */

void writerXML::writeLogin(QString url, QString login, QString date_created, QString owner)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash((url + login + "Chrome").toAscii(), QCryptographicHash::Md5).toHex();

    m_pXmlWriter->writeStartElement("doc");
    writeField("doc_type", "login");
    writeField("id", "chrome_" + md5Id);
    writeField("application", "chrome");
    writeField("owner", owner);
    writeField("login_param_url",url);
    writeField("login_param_login",login);
    writeField("login_param_date_create",date_created);

    m_pXmlWriter->writeEndElement();
}
