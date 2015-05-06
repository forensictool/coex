#include "writerMessages.h"
/*!
 * \brief writerMessagesPidgin::writerMessagesPidgin - Конструктор, по умолчанию создаётся указатель на xml файл.
 * Далее начинается запись в документ
 * \param fileName - Имя для создания выходного xml файла
 * \param messangerName - Имя приложения, для которого создаётся выходной файл
 */
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
    m_pXmlWriter->writeStartElement("add");
    //m_pXmlWriter->writeAttribute("Messenger" ,messangerName);
}
/*!
 * \brief writerMessagesPidgin::~writerMessagesPidgin - Деструктор, удаляет указатели на файл.
 * Закрывает поля в документе
 */
writerMessagesPidgin::~writerMessagesPidgin()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}
/*!
 * \brief writerMessagesPidgin::opened
 * \return [out] - Статус
 */
bool writerMessagesPidgin::opened()
{
    return m_bOpened;
}
/*!
 * \brief writerMessagesPidgin::writeAccountInfo_field - Запись информации в поле, и его значение
 * \param field_name - Имя поля
 * \param field_value - Его значение
 */
void writerMessagesPidgin::writeAccountInfo_field(
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
/*!
 * \brief writerMessagesPidgin::writeAccountInfo - Записывает информацию о аккаунте в Pidgin
 * \param name - Имя
 * \param email - Почта
 * \param protocol - Протокол, использованный для передачи сообщений
 * \param password - Пароль
 */
void writerMessagesPidgin::writeAccountInfo(
    QString name,
    QString email,
    QString protocol,
    QString password
)
{
    if (!m_bOpened)return;
    QString md5Id = QCryptographicHash::hash( (email+protocol+name+password).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeStartElement("doc");
    writeAccountInfo_field("doc_type", "account");
    writeAccountInfo_field("id", "pidgin_"+ md5Id);
    writeAccountInfo_field("application", "pidgin");
    writeAccountInfo_field("account_id", name);
    writeAccountInfo_field("account_mail", email);
    writeAccountInfo_field("account_protocol", protocol);
    writeAccountInfo_field("account_password", password);
    m_pXmlWriter->writeEndElement();
}
/*!
 * \brief writerMessagesPidgin::writeContactList - Записывает информацию о контактной книге Pidgin
 * \param account - Аккаунт
 * \param protocol - Протокол, использованный для передачи сообщений
 * \param alias - Имя
 * \param name - Идентификатор контакта
 */
void writerMessagesPidgin::writeContactList(
    QString account,
    QString protocol,
    QString alias,
    QString name
)
{
    if (!m_bOpened)return;
    QString md5Id = QCryptographicHash::hash( (protocol+account+name+alias).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeStartElement("doc");
    writeAccountInfo_field("doc_type", "contact");
    writeAccountInfo_field("id", "pidgin_"+ md5Id);
    writeAccountInfo_field("application", "pidgin");
    writeAccountInfo_field("contact_name", alias);
    writeAccountInfo_field("contact_account", account);
    writeAccountInfo_field("contact_protocol", protocol);
    writeAccountInfo_field("contact_id", name);
    m_pXmlWriter->writeEndElement();
}
/*!
 * \brief writerMessagesPidgin::writeMessage - Запись сообщения
 * \param chathID - Идентификатор чата
 * \param account - Аккаунт
 * \param protocol - Протокол, использованный для передачи сообщений
 * \param author - Автор
 * \param dataTime - Время отправки/принятия сообщения
 * \param message - Текст сообщения
 */
void writerMessagesPidgin::writeMessage(
    QString chathID,
    QString account,
    QString protocol,
    QString author,
    QString dataTime,
    QString message
)
{
    if (!m_bOpened)return;
    QString md5Id = QCryptographicHash::hash((chathID+account+protocol+author+dataTime+message).toAscii(), QCryptographicHash::Md5 ).toHex();
    m_pXmlWriter->writeStartElement("doc");
    writeAccountInfo_field("doc_type", "message");
    writeAccountInfo_field("id", "pidgin_"+ md5Id);
    writeAccountInfo_field("application", "pidgin");
    writeAccountInfo_field("message_chat_id", chathID);
    writeAccountInfo_field("message_account", account);
    writeAccountInfo_field("message_protocol", protocol);
    writeAccountInfo_field("message_author", author);
    writeAccountInfo_field("message_dataTime", dataTime);
    writeAccountInfo_field("message_text", message);
    m_pXmlWriter->writeEndElement();
}
