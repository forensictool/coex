#include <QCryptographicHash>
#include "writerMessages.h"

writerMessages::writerMessages()
{
}
writerMessages::~writerMessages()
{
}
bool writerMessages::opened()
{
}

bool writerMessagesSkype::opened()
{
    return m_bOpened;
}


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
//destructor
writerMessagesSkype::~writerMessagesSkype()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}

// like skype
void writerMessagesSkype::writeMessage(
        QString author,
        QString timestamp,
        QString body_xml
)

{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("doc");

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "id");
    QString md5Id = QCryptographicHash::hash( (author+timestamp+body_xml).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeCharacters("skype_"+ md5Id);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "doc-type");
    m_pXmlWriter->writeCharacters("log");
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "log_author");
    m_pXmlWriter->writeCharacters(author);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    bool isconverted;
    uint iunixtime_integer = timestamp.toUInt(&isconverted);
    QString idatetime = QDateTime::fromTime_t(iunixtime_integer).toString();
    m_pXmlWriter->writeAttribute("name", "log_timestamp");
    m_pXmlWriter->writeCharacters(idatetime);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "log_message");
    m_pXmlWriter->writeCharacters(body_xml);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeEndElement();
};


void writerMessagesSkype::writeCalls(
    QString begin_timestamp,
    QString duration,
    QString host_identity,
    QString current_video_audience
)

{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("doc");

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "id");
    QString md5Id = QCryptographicHash::hash( (begin_timestamp+duration+host_identity+current_video_audience).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeCharacters("skype_"+ md5Id);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "doc-type");
    m_pXmlWriter->writeCharacters("call");
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    bool isconverted;
    uint iunixtime_integer = begin_timestamp.toUInt(&isconverted);
    QString idatetime = QDateTime::fromTime_t(iunixtime_integer).toString();
    m_pXmlWriter->writeAttribute("name", "call_timestamp");
    m_pXmlWriter->writeCharacters(idatetime);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "call_duration");
    m_pXmlWriter->writeCharacters(duration);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "call_server");
    m_pXmlWriter->writeCharacters(host_identity);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "call_client");
    m_pXmlWriter->writeCharacters(current_video_audience);
    m_pXmlWriter->writeEndElement();

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
    m_pXmlWriter->writeStartElement("doc");

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "id");
    QString md5Id = QCryptographicHash::hash( (skypename+fullName+birthday+gender+phone_mobile+languages+country+city).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeCharacters("skype_"+ md5Id);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "doc-type");
    m_pXmlWriter->writeCharacters("contact");
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "contact_name");
    m_pXmlWriter->writeCharacters(skypename);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "contact_fullName");
    m_pXmlWriter->writeCharacters(fullName);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "contact_birthday");
    m_pXmlWriter->writeCharacters(birthday);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "contact_phone");
    m_pXmlWriter->writeCharacters(phone_mobile);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    if (gender == "1")
        gender = "Male";
    else if (gender == "2")
        gender = "Felmale";
    else
        gender = "Unknow";
    m_pXmlWriter->writeAttribute("name", "contact_gender");
    m_pXmlWriter->writeCharacters(gender);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "contact_languages");
    m_pXmlWriter->writeCharacters(languages);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "contact_country");
    m_pXmlWriter->writeCharacters(country);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "contact_city");
    m_pXmlWriter->writeCharacters(city);
    m_pXmlWriter->writeEndElement();

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
    m_pXmlWriter->writeStartElement("doc");

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "id");
    QString md5Id = QCryptographicHash::hash( (fullName+ipcountry+emails+fullName+skypeName).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeCharacters("skype_"+ md5Id);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "doc-type");
    m_pXmlWriter->writeCharacters("account");
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "account_name");
    m_pXmlWriter->writeCharacters(skypeName);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "account_fullName");
    m_pXmlWriter->writeCharacters(fullName);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "account_emails");
    m_pXmlWriter->writeCharacters(emails);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeStartElement("field");
    m_pXmlWriter->writeAttribute("name", "account_ipcountry");
    m_pXmlWriter->writeCharacters(ipcountry);
    m_pXmlWriter->writeEndElement();

    m_pXmlWriter->writeEndElement();
};
