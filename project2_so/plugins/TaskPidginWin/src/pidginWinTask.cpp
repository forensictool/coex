#include "pidginWinTask.h"

#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>

QString getLibName()
{
	return(QString("pidginWinTask"));
}

bool m_bDebug = true;

bool execute(const coex::config& config)
{
	if(m_bDebug)
	std::cout << "  !!! debug mode on.\n";
	{
		QDir dir(config.outputFolder);
		dir.mkdir("pidgin");
	}
	if(m_bDebug)
	std::cout << "===========================================\n\n";
	QString path = config.inputFolder + "/Users/";
	QDir dir(path);
	dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
	QFileInfoList users = dir.entryInfoList();
	QStringList foundFile;
	for( int i = 0; i < users.size();++i)
	{
		QFileInfo fileInfo = users.at(i);
		path = fileInfo.absoluteFilePath() + "/AppData/Roaming/.purple/logs";
		QDirIterator dirPath (path, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
		while(dirPath.hasNext())
		{
			QFileInfo fileInfo = dirPath.next();
			if (fileInfo.suffix() == "html" || fileInfo.suffix() == "txt")
			{
				foundFile << fileInfo.absoluteFilePath();
			}
		}
	}
    writerMessagesPidgin pidginMessages(config.outputFolder + "//pidgin/messages.xml", "pidgin");
    writerMessagesPidgin pidginAccount(config.outputFolder + "//pidgin/accounts.xml", "pidgin");
    writerMessagesPidgin pidginContacts(config.outputFolder + "//pidgin/contacts.xml", "pidgin");
    if(!pidginMessages.opened()||!pidginAccount.opened()||!pidginContacts.opened())
	{
		std::cout << " failed task\n";
		return false;
	}

    QString name;
    QString email;
    QString protocol;
    QString password;

    QFile fileXmlAccount(config.inputFolder + "/Users/Default/AppData/Roaming/.purple/accounts.xml");
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&fileXmlAccount);

    QString nameElem = "";
    if(fileXmlAccount.open(QIODevice::ReadOnly))
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
				if(nameElem == "name") 
					name += xmlReader.text().toString();
				else if (nameElem == "password")
					password += xmlReader.text().toString();
				else if (nameElem == "protocol")
					protocol += xmlReader.text().toString();
				else if (nameElem == "email")
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
					
					if(m_bDebug)
						std::cout <<"\npidginAccount::1:: " << name.toStdString()
							<< "\npidginAccount::2:: "<< email.toStdString()
							<<"\npidginAccount::3:: "<< protocol.toStdString()
							<<"\npidginAccount::4:: " << password.toStdString() <<"\n";
					
				}
            }
        }
    }
    else
    {
        std::cout << "could not opening file \r\n";
    };

    QString accountPidgin;
    QString protoPidgin;
    QString namePidgin;
    QString emailPidgin;

    QFile fileXmlContacts(config.inputFolder + "/Users/Default/AppData/Roaming/.purple/blist.xml");
    //QXmlStreamReader xmlReader;
    xmlReader.setDevice(&fileXmlContacts);

    //QString nameElem = "";
    if(fileXmlContacts.open(QIODevice::ReadOnly))
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
                if (xmlReader.name() == "buddy") {
                    accountPidgin = "";
                    protoPidgin = "";
                    namePidgin = "";
                    emailPidgin = "";
                }
            }

            // запоминаем текст исходя из имени элемента
            if(token == QXmlStreamReader::Characters) {
                if(nameElem == "account")
                    accountPidgin += xmlReader.text().toString();
                else if (nameElem == "name")
                    emailPidgin += xmlReader.text().toString();
                else if (nameElem == "alias")
                    namePidgin += xmlReader.text().toString();
                else if (nameElem == "proto")
                    protoPidgin += xmlReader.text().toString();
            }

            // все когда встречаем элемент конца то сбрасываем все данные в writer
            if(token == QXmlStreamReader::EndElement)
            {
                if (xmlReader.name() == "buddy") {
                    accountPidgin = accountPidgin.trimmed();
                    protoPidgin = protoPidgin.trimmed();
                    namePidgin = namePidgin.trimmed();
                    emailPidgin = emailPidgin.trimmed();
                    pidginContacts.writeContactList(accountPidgin,protoPidgin,namePidgin,emailPidgin);

                    if(m_bDebug)
                        std::cout <<"\npidginContact::1:: " << accountPidgin.toStdString()
                            << "\npidginContact::2:: "<< protoPidgin.toStdString()
                            <<"\npidginContact::3:: "<< namePidgin.toStdString()
                            <<"\npidginContact::4:: " << emailPidgin.toStdString() <<"\n";

                }
            }
        }
    }
    else
    {
        std::cout << "could not opening file \r\n";
    };


    QString time;
	QString author;
	QString message;
	QString chatID;
	QString account;
	QString data;

	for(int i = 0; i < foundFile.size(); ++i)
	{
		QFileInfo fileInfo = foundFile.at(i);
		if (fileInfo.suffix() == "html")
		{
            QFile fileHtmlLogs(fileInfo.absoluteFilePath());
            if (fileHtmlLogs.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				QRegExp rxHead(".*h3.*with (.*) at (.*) \\d{2}:\\d{2}:\\d{2} on (.*) .*\\((.*)\\)");
				/*Parse string like this (one string):
				*  <html><head><meta http-equiv="content-type" content="text/html; charset=UTF-8"><title>
				*  Conversation with dog.user@mail.ru at Сб. 04 мая 2013 15:49:00 on cat.user@mail.ru (icq)
				*  </title></head><body><h3>Conversation with dog.user@mail.ru at Сб. 04 мая 2013 15:49:00 on cat.user@mail.ru (icq)</h3>                 *
				*/
                QTextStream in(&fileHtmlLogs);
                QString line = fileHtmlLogs.readLine();//read first line, get interesting info)
				rxHead.indexIn(line);
				chatID = rxHead.cap(1);
				account = rxHead.cap(3);
				data = rxHead.cap(2);
                namePidgin = rxHead.cap(4);
				if(m_bDebug)
                std::cout <<"\n Mess::1:: "<< chatID.toStdString() <<"\n Mess::2:: "<< account.toStdString() <<"\n Mess::3:: "<< data.toStdString() <<"\n Mess::4:: " << namePidgin.toStdString() <<"\n";
                pidginMessages.writeInfoLog(chatID, data, account, namePidgin);
				QRegExp rxBody(".*(\\d{2}:\\d{2}:\\d{2}).*b\\>(.*):\\<\\/b.*font\\>(.*)\\<br");
				while(!in.atEnd())
				{
					line = in.readLine(); // read all file
					rxBody.indexIn(line);
					time = rxBody.cap(1);
					author = rxBody.cap(2);
					message = rxBody.cap(3);
                    pidginMessages.writeMessage(author,data + " " + time,message);
				}
			}
			else
			{
				std::cout << "could not opening file: " << fileInfo.absolutePath().toStdString() << "\r\n";
			}
		}
		if (fileInfo.suffix() == "txt")
		{
            QFile fileTxtLog(fileInfo.absoluteFilePath());
			// open a file
            if (fileTxtLog.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				QRegExp rxHead(".*with (.*) at (.*) on (.*)\\/ \\((.*)\\)");
                QString line = fileTxtLog.readLine();//read first line, get interesting info)
				rxHead.indexIn(line);
				chatID = rxHead.cap(1);
				account = rxHead.cap(2);
				data = rxHead.cap(3);
                namePidgin = rxHead.cap(4);
				if(m_bDebug)
                std::cout <<"\n::1:: "<< chatID.toStdString() <<"\n ::2:: "<< account.toStdString() <<"\n ::3:: "<< data.toStdString() <<"\n ::4:: " << namePidgin.toStdString() <<"\n";
                pidginMessages.writeInfoLog(chatID, data, account, namePidgin);
				QRegExp rxBody("\\((\\d{2}:\\d{2}:\\d{2})\\)[ ]*(.*):(.*)$");
                while(!fileTxtLog.atEnd())
				{
                    line = fileTxtLog.readLine();
					rxBody.indexIn(line);
					time = rxBody.cap(1);
					author = rxBody.cap(2);
					message = rxBody.cap(3);
                    pidginMessages.writeMessage(author,time,message);
				}
			}
			else
			{
				std::cout << "could not opening file: " << fileInfo.absolutePath().toStdString() << "\r\n";
			}
		}
	}
	if(m_bDebug)
	std::cout << "===========================================\n\n";
	return true;
}

writerMessages::writerMessages()
{
}
writerMessages::~writerMessages()
{
}
bool writerMessages::opened()
{
	return m_bOpened;
}

bool writerMessagesPidgin::opened()
{
    return m_bOpened;
}

writerMessagesPidgin::writerMessagesPidgin(QString fileName, QString messangerName)
{
    m_bOpened = true;
    m_pFile = new QFile(fileName);
    if (!m_pFile->open(QIODevice::Append))
    {
        //std::cout << " failed task\n";
        m_bOpened = false;
        return;
    }
    m_pXmlWriter = new QXmlStreamWriter();
    m_pXmlWriter->setDevice(m_pFile);

    m_pXmlWriter->setAutoFormatting(true);
    m_pXmlWriter->writeStartDocument();
    m_pXmlWriter->writeStartElement("Messages ");
    m_pXmlWriter->writeAttribute("Messenger" ,messangerName);
}

writerMessagesPidgin::~writerMessagesPidgin()
{
    m_pXmlWriter->writeEndElement();
    m_pXmlWriter->writeEndDocument();
    delete m_pXmlWriter;
    delete m_pFile;
}

//about account.xml file
void writerMessagesPidgin::writeAccountInfo(
    QString name,
    QString email,
    QString protocol,
    QString password
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("info_account");
    m_pXmlWriter->writeAttribute("name", name);
    m_pXmlWriter->writeAttribute("email", email);
    m_pXmlWriter->writeAttribute("password", password);
    m_pXmlWriter->writeAttribute("protocol", protocol);
    m_pXmlWriter->writeEndElement();
}

//about contacts.xml file
void writerMessagesPidgin::writeContactList(
    QString account,
    QString protocol,
    QString alias,
    QString name
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("Contact_list");
    m_pXmlWriter->writeAttribute("account", account);
    m_pXmlWriter->writeAttribute("protocol", protocol);
    m_pXmlWriter->writeAttribute("name", alias);
    m_pXmlWriter->writeAttribute("emails", name);
    m_pXmlWriter->writeEndElement();
}

//about log file
void writerMessagesPidgin::writeInfoLog(
    QString chathID,
    QString account,
    QString data,
    QString protocol
)
{
    if (!m_bOpened) return;
    m_pXmlWriter->writeStartElement("info");
    m_pXmlWriter->writeAttribute("chathID", chathID);
    m_pXmlWriter->writeAttribute("account", account);
    m_pXmlWriter->writeAttribute("data", data);
    m_pXmlWriter->writeAttribute("protocol", protocol);
    m_pXmlWriter->writeEndElement();
}

//like pidgin
void writerMessagesPidgin::writeMessage(
    QString author,
    QString dataTime,
    QString message
)
{
    if (!m_bOpened)return;
    m_pXmlWriter->writeStartElement("message");
    m_pXmlWriter->writeAttribute("author", author);
    m_pXmlWriter->writeAttribute("dataTime", dataTime);
    m_pXmlWriter->writeAttribute("message", message);
    m_pXmlWriter->writeEndElement();
}

