#include "pidginWinTask.h"
#include "writerMessages.h"
/*!
    \brief Класс для обработки логов Pidgin
    \author Polyakov Igor
    \version 1.0
    \date Март 2015 года
    \warning Данный класс создан только в учебных целях
    Обычный дочерний класс, который наследован от ранее созданного класса coex
*/
TaskPidginWin::TaskPidginWin()
{
    m_bDebug = false;
};
QString TaskPidginWin::help()
{
    return "\t--debug - viewing debug messages";
};
QString TaskPidginWin::name()
{
    return "PidginWin";
};
QString TaskPidginWin::author()
{
    return "Igor Polyakov";
};
QString TaskPidginWin::description()
{
    return "Task is search logs of Pidgin for WINDOWS";
};
bool TaskPidginWin::isSupportOS(const coex::ITypeOperationSystem *os)
{
    return (os->platform() == "Windows" && (os->version() == "XP" || os->version() == "7"));
};
void TaskPidginWin::setOption(QStringList options)
{
    /*
    *
    * */
    if (options.contains("--debug"))
        m_bDebug = true;
};

/*!
 * \brief TaskPidginWin::processingContactListPidgin - Вычитывает xml файл контактов Pidgin с данными. Преобразует к структурированному xml
 * \param[in] inputFile Путь к обрабатываемому файлу
 * \param[out] outPath Папка в которой лежат собранные данные
 */
void TaskPidginWin::processingContactListPidgin(QString inputFile, QString outPath)
{
    QXmlStreamReader xmlReader;
    QFile fileXmlContacts(inputFile);
    xmlReader.setDevice(&fileXmlContacts);
    writerMessagesPidgin pidginContacts(outPath + "//pidgin/contacts.xml", "pidgin");
    QString accountPidgin, protoPidgin, namePidgin, emailPidgin;
    QString nameElem = "";
    if (fileXmlContacts.open(QIODevice::ReadOnly)) {
        xmlReader.readNext();
        while (!xmlReader.atEnd() && !xmlReader.hasError()) {
            QXmlStreamReader::TokenType token = xmlReader.readNext();
            if (token == QXmlStreamReader::StartDocument) {
                continue;
            }
            if (token == QXmlStreamReader::StartElement) {
                nameElem = xmlReader.name().toString();
                if (xmlReader.name() == "buddy") {
                    foreach(const QXmlStreamAttribute & attr, xmlReader.attributes()) {
                        if (attr.name().toString() == QLatin1String("account")) {
                            accountPidgin = attr.value().toString();
                        } else if (attr.name().toString() == QLatin1String("proto")) {
                            protoPidgin = attr.value().toString();
                        }
                    }
                    namePidgin = "";
                    emailPidgin = "";
                }
            }
            if (token == QXmlStreamReader::Characters) {
                if (nameElem == "name")
                    emailPidgin += xmlReader.text().toString();
                else if (nameElem == "alias")
                    namePidgin += xmlReader.text().toString();
            }
            if (token == QXmlStreamReader::EndElement) {
                if (xmlReader.name() == "buddy") {
                    accountPidgin = accountPidgin.trimmed();
                    protoPidgin = protoPidgin.trimmed();
                    namePidgin = namePidgin.trimmed();
                    emailPidgin = emailPidgin.trimmed();
                    pidginContacts.writeContactList(accountPidgin, protoPidgin, namePidgin, emailPidgin);
                }
            }
        }
    } else {
        qDebug() << "could not opening contacts file \r\n";
    };
};

/*!
 * \brief TaskPidginWin::processingAccountPidgin - Вычитывает xml файл аккаунта Pidgin. Преобразует к структурированному xml
 * \param[in] inputFile Путь к обрабатываемому файлу
 * \param[out] outPath Папка в которой лежат собранные данные
 */
void TaskPidginWin::processingAccountPidgin(QString inputFile, QString outPath)
{
    QFile foundFile(inputFile);
    writerMessagesPidgin pidginAccount(outPath + "//pidgin/accounts.xml", "pidgin");
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&foundFile);
    QString name, email, protocol, password, nameElem = "";
    if (foundFile.open(QIODevice::ReadOnly)) {
        xmlReader.readNext();
        while (!xmlReader.atEnd() && !xmlReader.hasError()) {
            QXmlStreamReader::TokenType token = xmlReader.readNext();
            if (token == QXmlStreamReader::StartDocument) {
                continue;
            }
            if (token == QXmlStreamReader::StartElement) {
                nameElem = xmlReader.name().toString();
                if (xmlReader.name() == "account") {
                    name = "";
                    email = "";
                    protocol = "";
                    password = "";
                }
            }
            if (token == QXmlStreamReader::Characters) {
                if (nameElem == "alias")
                    name += xmlReader.text().toString();
                else if (nameElem == "password")
                    password += xmlReader.text().toString();
                else if (nameElem == "protocol")
                    protocol += xmlReader.text().toString();
                else if (nameElem == "name")
                    email += xmlReader.text().toString();
            }
            if (token == QXmlStreamReader::EndElement) {
                if (xmlReader.name() == "account") {
                    name = name.trimmed();
                    email = email.trimmed();
                    protocol = protocol.trimmed();
                    password = password.trimmed();
                    pidginAccount.writeAccountInfo(name, email, protocol, password);
                }
            }
        }
    } else {
        qDebug() << "Could not opening accounts.xml file \r\n";
    };
};

/*!
 * \brief TaskPidginWin::processingLogPidgin - Вычитывает журнальные файлы Pidgin. Формат файлов html, txt.
 * Преобразует к структурированному формату xml
 * \param fileInfo - Информация о обрабатываемом файле.
 * \param outputPath - Путь для выходных данные
 */
void TaskPidginWin::processingLogPidgin(QFileInfo  fileInfo, QString outputPath)
{
    QString md5Id = QCryptographicHash::hash(fileInfo.filePath().toAscii(), QCryptographicHash::Sha1).toHex();
    writerMessagesPidgin pidginMessages(outputPath + "//pidgin/messages/" + md5Id + ".xml", "pidgin");
    QString time, author, message, chatID, account, data, namePidgin;
    QFile fileLogs(fileInfo.absoluteFilePath());
    QRegExp rxHead, rxBody;
    if (fileLogs.open(QIODevice::ReadOnly | QIODevice::Text)) {
        if (fileInfo.suffix() == "html") {
            rxHead.setPattern(".*h3.*with (.*) at (.*) \\d{2}:\\d{2}:\\d{2} on (.*) .*\\((.*)\\)");
        } else if (fileInfo.suffix() == "txt") {
            rxHead.setPattern(".* with (.*) at (.*) on (.*) \\((.*)\\)");
        }
        QString line = fileLogs.readLine();//read first line, get interesting info)
        rxHead.indexIn(line);
        chatID = rxHead.cap(1);
        account = rxHead.cap(3);
        data = rxHead.cap(2);
        namePidgin = rxHead.cap(4);
        if (fileInfo.suffix() == "html") {
            rxBody.setPattern(".*(\\d{2}:\\d{2}:\\d{2}).*b\\>(.*):\\<\\/b.*font\\>(.*)\\<br");
        } else if (fileInfo.suffix() == "txt") {
            rxBody.setPattern("\\((.*\\d{2}:\\d{2}:\\d{2})\\) (.*): (.*)");
        }
        while (!fileLogs.atEnd()) {
            line = fileLogs.readLine(); // read all file
            rxBody.indexIn(line);
            time = rxBody.cap(1);
            author = rxBody.cap(2);
            message = rxBody.cap(3);
            pidginMessages.writeMessage(chatID, account, namePidgin, author, data + " " + time, message);
        }
    } else {
        qDebug() << "could not opening log file: " << fileInfo.absolutePath() << "\r\n";
    }
};

/*!
 * \brief TaskPidginWin::execute - Некий main класса TaskPidginWin
 * \param [in] config лист с путями входными, выходными
 * \return Возвращает статус исполнения плагина
 */
bool TaskPidginWin::execute(const coex::IConfig *config)
{
    if (m_bDebug) {
        qDebug() << "===========================================\n\n";
        qDebug() << "Debug mode ON\n";
        qDebug() << "InputFolder: " << config->inputFolder() << "\n";
    };
    QDir dir(config->outputFolder());
    dir.mkdir("pidgin");
    dir.mkdir("pidgin/messages");
    QRegExp pidginPathAccount(".*purple/accounts.xml");
    QRegExp pidginPathContact(".*purple/blist.xml");
    QRegExp pidginPathLogHtml(".*purple/logs.*html");
    QRegExp pidginPathLogTxt(".*purple/logs.*txt");
    TaskPidginWin account, contact, log;
    QDirIterator dirPath(config->inputFolder(), QDir::Files | QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
    while (dirPath.hasNext()) {
        if (dirPath.filePath().contains(pidginPathAccount)) {
            account.processingAccountPidgin(dirPath.filePath(), config->outputFolder());
            dirPath.next();
        } else if (dirPath.filePath().contains(pidginPathContact)) {
            contact.processingContactListPidgin(dirPath.filePath(), config->outputFolder());
            dirPath.next();
        } else if (dirPath.filePath().contains(pidginPathLogTxt) || dirPath.next().contains(pidginPathLogHtml)) {
            log.processingLogPidgin(dirPath.fileInfo(), config->outputFolder());
            dirPath.next();
        }
    };
    return true;
};

/*!
 * \brief createTask — Создание плагина, и его выполнение
 * \return
 */
coex::ITask* createTask()
{
    return (coex::ITask*)(new TaskPidginWin());
}
