#include "pidginWinTask.h"
#include "writerMessages.h"

#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QCryptographicHash>

TaskPidginWin::TaskPidginWin() {
    m_bDebug = false;
};

QString TaskPidginWin::help() {
	return "\t--debug - viewing debug messages";
};

QString TaskPidginWin::name() {
	return "pidgin-win";
};

QString TaskPidginWin::author() {
	return "Igor Polyakov";
};

QString TaskPidginWin::description() {
	return "Task is search logs of Pidgin for WINDOWS";
};

bool TaskPidginWin::isSupportOS(const coex::ITypeOperationSystem *os) {
	return (os->platform() == "Windows" && (os->version() == "XP" || os->version() == "7"));
};

void TaskPidginWin::setOption(QStringList options) {
	/*
	* 
	* */
	if(options.contains("--debug"))
	m_bDebug = true;
};

void processingContactListPidgin(QString inputFile, QString outPath){
    QXmlStreamReader xmlReader;
    QFile fileXmlContacts (inputFile);
    xmlReader.setDevice(&fileXmlContacts);
    writerMessagesPidgin pidginContacts(outPath + "//pidgin/contacts.xml", "pidgin");
    QString accountPidgin, protoPidgin, namePidgin, emailPidgin;
    QString nameElem = "";
    if(fileXmlContacts.open(QIODevice::ReadOnly))
    {
        xmlReader.readNext();
        while(!xmlReader.atEnd() && !xmlReader.hasError())
        {
            QXmlStreamReader::TokenType token = xmlReader.readNext();
            if(token == QXmlStreamReader::StartDocument)
            {
                continue;
            }
            if(token == QXmlStreamReader::StartElement)
            {
                nameElem = xmlReader.name().toString();

                if (xmlReader.name() == "buddy") {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes()) {
                        if (attr.name().toString() == QLatin1String("account")) {
                            accountPidgin = attr.value().toString();
                        }
                        else if (attr.name().toString() == QLatin1String("proto")) {
                            protoPidgin = attr.value().toString();
                        }
                    }
                    namePidgin = "";
                    emailPidgin = "";
                }
            }
            if(token == QXmlStreamReader::Characters) {
                if (nameElem == "name")
                emailPidgin += xmlReader.text().toString();
                else if (nameElem == "alias")
                namePidgin += xmlReader.text().toString();
            }
            if(token == QXmlStreamReader::EndElement)
            {
                if (xmlReader.name() == "buddy") {
                    accountPidgin = accountPidgin.trimmed();
                    protoPidgin = protoPidgin.trimmed();
                    namePidgin = namePidgin.trimmed();
                    emailPidgin = emailPidgin.trimmed();
                    pidginContacts.writeContactList(accountPidgin,protoPidgin,namePidgin,emailPidgin);
                }
            }
        }
    }
    else
    {
        std::cout << "could not opening contacts file \r\n";
    };

};

void processingAccountPidgin(QString inputFile, QString outPath){
    QFile foundFile (inputFile);
    writerMessagesPidgin pidginAccount(outPath + "//pidgin/accounts.xml", "pidgin");
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&foundFile);
    QString name, email, protocol, password, nameElem = "";
    if(foundFile.open(QIODevice::ReadOnly))
    {
        xmlReader.readNext();
        while(!xmlReader.atEnd() && !xmlReader.hasError())
        {
            //std::cout << "cyrcle";
            QXmlStreamReader::TokenType token = xmlReader.readNext();

            // пропускаем рутовый элемент документа
            if(token == QXmlStreamReader::StartDocument)
            {
                continue;
            }
            if(token == QXmlStreamReader::StartElement)
            {
                // запоминаем имя текущего элемента
                nameElem = xmlReader.name().toString();

                // когда встречаем элемент то вычищаем наши переменные
                if (xmlReader.name() == "account") {
                    name = "";
                    email = "";
                    protocol = "";
                    password = "";
                }
            }

            // запоминаем текст исходя из имени элемента
            if(token == QXmlStreamReader::Characters) {
                if(nameElem == "alias")
                name += xmlReader.text().toString();
                else if (nameElem == "password")
                password += xmlReader.text().toString();
                else if (nameElem == "protocol")
                protocol += xmlReader.text().toString();
                else if (nameElem == "name")
                email += xmlReader.text().toString();
            }

            // все когда встречаем элемент конца то сбрасываем все данные в writer
            if(token == QXmlStreamReader::EndElement)
            {
                if (xmlReader.name() == "account") {
                    name = name.trimmed();
                    email = email.trimmed();
                    protocol = protocol.trimmed();
                    password = password.trimmed();
                    pidginAccount.writeAccountInfo(name,email,protocol,password);
                }
            }
        }
    }
    else
    {
        std::cout << "Could not opening accounts.xml file \r\n";
    };
};

void processingLogPidgin(QFileInfo  fileInfo, QString outputPath){

    QString md5Id = QCryptographicHash::hash( fileInfo.filePath().toAscii(), QCryptographicHash::Sha1 ).toHex();

    writerMessagesPidgin pidginMessages(outputPath + "//pidgin/messages/" + md5Id + ".xml", "pidgin");
    QString time, author,message, chatID, account, data, namePidgin;

    QFile fileLogs(fileInfo.absoluteFilePath());
    QRegExp rxHead, rxBody;

    if (fileLogs.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if (fileInfo.suffix() == "html")
        {
            rxHead.setPattern(".*h3.*with (.*) at (.*) \\d{2}:\\d{2}:\\d{2} on (.*) .*\\((.*)\\)");
        }
        else if (fileInfo.suffix() == "txt")
        {
            rxHead.setPattern(".* with (.*) at (.*) on (.*) \\((.*)\\)");
        }
        QString line = fileLogs.readLine();//read first line, get interesting info)
        qDebug() << line;
        rxHead.indexIn(line);
        chatID = rxHead.cap(1);
        account = rxHead.cap(3);
        data = rxHead.cap(2);
        namePidgin = rxHead.cap(4);
        pidginMessages.writeInfoLog(chatID, data, account, namePidgin);
        if (fileInfo.suffix() == "html")
        {
            rxBody.setPattern(".*(\\d{2}:\\d{2}:\\d{2}).*b\\>(.*):\\<\\/b.*font\\>(.*)\\<br");
        }
        else if (fileInfo.suffix() == "txt")
        {
            rxBody.setPattern("\\((.*\\d{2}:\\d{2}:\\d{2})\\) (.*): (.*)");
        }

        while(!fileLogs.atEnd())
        {
            line = fileLogs.readLine(); // read all file
            rxBody.indexIn(line);
            time = rxBody.cap(1);
            author = rxBody.cap(2);
            message = rxBody.cap(3);
            pidginMessages.writeMessage(author,data + " " + time,message);
        }
    }
    else
    {
        std::cout << "could not opening log file: " << fileInfo.absolutePath().toStdString() << "\r\n";
    }
};

bool TaskPidginWin::execute(const coex::IConfig *config) {
	if(m_bDebug) {
        std::cout << "===========================================\n\n";
        std::cout << "Debug mode ON\n";
		std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
	};
    {
        QDir dir(config->outputFolder());
        dir.mkdir("pidgin");
        dir.mkdir("pidgin/messages");

    }
    //QString path = config->inputFolder() + "/Users/";
    QString path = config->inputFolder();
    QRegExp pidginPathAccount(".*purple/accounts.xml");
    QRegExp pidginPathContact(".*purple/blist.xml");
    QRegExp pidginPathLogHtml(".*purple/logs.*html");
    QRegExp pidginPathLogTxt(".*purple/logs.*txt");

    QDirIterator dirPath (path, QDir::Files | QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
    while(dirPath.hasNext())
    {
        if (dirPath.filePath().contains(pidginPathAccount))
        {
            processingAccountPidgin(dirPath.filePath(), config->outputFolder());
            dirPath.next();
        }
        else if (dirPath.filePath().contains(pidginPathContact))
        {
            processingContactListPidgin(dirPath.filePath(), config->outputFolder());
            dirPath.next();
        }
        else if ( dirPath.filePath().contains(pidginPathLogTxt) || dirPath.next().contains(pidginPathLogHtml) )
        {
            qDebug() << dirPath.filePath();
            processingLogPidgin(dirPath.fileInfo(), config->outputFolder());
            dirPath.next();
        }
    };
	return true;
};

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskPidginWin());
}
