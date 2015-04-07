#include "writerMessagesSkype.h"

//constructor
writerMessagesSkype::writerMessagesSkype(
    QString fileType
)
{
    m_bOpened = true;
    m_pFile= new QFile(fileType);
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

writerMessagesSkype::~writerMessagesSkype()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}

bool writerMessagesSkype::opened()
{
    return m_bOpened;
}

void writerMessagesSkype::writeSkype_field(
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
// like skype
void writerMessagesSkype::writeMessage(
        QString author,
        QString timestamp,
        QString body_xml
)
{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash( (author+timestamp+body_xml).toAscii(), QCryptographicHash::Md5 ).toHex();
    bool isconverted;
    uint iunixtime_integer = timestamp.toUInt(&isconverted);
    QString idatetime = QDateTime::fromTime_t(iunixtime_integer).toString();

    m_pXmlWriter->writeStartElement("doc");

    writeSkype_field("doc_type", "message");
    writeSkype_field("id", "skype_"+ md5Id);
    writeSkype_field("application", "skype");
    writeSkype_field("message_author", author);
    writeSkype_field("message_dataTime", idatetime);
    writeSkype_field("message_text", body_xml.remove(QRegExp("[^а-яА-Яa-zA-Z\\d\\s]")));/*
    //hack allows you to remove the special characters in the future, you need to fix it*/
    m_pXmlWriter->writeEndElement();
}

void writerMessagesSkype::writeCalls(
    QString begin_timestamp,
    QString duration,
    QString host_identity,
    QString current_video_audience
)

{
    if (!m_bOpened)return;
    bool isconverted;
    uint iunixtime_integer = begin_timestamp.toUInt(&isconverted);
    QString idatetime = QDateTime::fromTime_t(iunixtime_integer).toString();
    QString md5Id = QCryptographicHash::hash( (begin_timestamp+duration+host_identity+current_video_audience).toAscii(), QCryptographicHash::Md5 ).toHex();

    m_pXmlWriter->writeStartElement("doc");

    writeSkype_field("doc_type", "contact");
    writeSkype_field("id", "pidgin_"+ md5Id);
    writeSkype_field("application", "pidgin");
    writeSkype_field("call_server", host_identity);
    writeSkype_field("call_client", current_video_audience);
    writeSkype_field("call_timestamp", idatetime);
    writeSkype_field("call_duration", duration);

    m_pXmlWriter->writeEndElement();
};


// like skype contact
void writerMessagesSkype::writeContacts(
        QString skypename,
        QString fullName,
        QString birthday,
        QString gender,
        QString phone_mobile,
        QString languages,
        QString country,
        QString city
)

{
    if (!m_bOpened)return;

    QString md5Id = QCryptographicHash::hash( (skypename+fullName+birthday+gender+phone_mobile+languages+country+city).toAscii(), QCryptographicHash::Md5 ).toHex();
    if (gender == "1")
        gender = "Male";
    else if (gender == "2")
        gender = "Felmale";
    else
        gender = "Unknow";
    m_pXmlWriter->writeStartElement("doc");

    writeSkype_field("doc_type", "contact");
    writeSkype_field("id", "skype_"+ md5Id);
    writeSkype_field("application", "skype");
    writeSkype_field("contact_name", skypename);
    writeSkype_field("contact_fullName", fullName);
    writeSkype_field("contact_birthday", birthday);
    writeSkype_field("contact_phone", phone_mobile);
    writeSkype_field("contact_gender", gender);
    writeSkype_field("contact_languages", languages);
    writeSkype_field("contact_country", country);
    writeSkype_field("contact_city", city);

    m_pXmlWriter->writeEndElement();
};

void writerMessagesSkype::writeInfo(
    QString skypeName,
    QString fullName,
    QString emails,
    QString ipcountry
)

{
    if (!m_bOpened)return;
    QString md5Id = QCryptographicHash::hash( (fullName+ipcountry+emails+fullName+skypeName).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeStartElement("doc");

    writeSkype_field("doc_type", "account");
    writeSkype_field("id", "skype_"+ md5Id);
    writeSkype_field("application", "skype");
    writeSkype_field("account_name", skypeName);
    writeSkype_field("account_fullName", fullName);
    writeSkype_field("account_emails", emails);
    writeSkype_field("account_ipcountry", ipcountry);

    m_pXmlWriter->writeEndElement();
};
