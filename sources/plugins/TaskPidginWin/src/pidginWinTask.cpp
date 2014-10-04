#include "pidginWinTask.h"
#include "writerMessages.h"

#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>

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

bool TaskPidginWin::execute(const coex::IConfig *config) {
	if(m_bDebug) {
        std::cout << "===========================================\n\n";
        std::cout << "Debug mode ON\n";
		std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
	};
    {
        QDir dir(config->outputFolder());
        dir.mkdir("pidgin");
    }
	QString path = config->inputFolder() + "/Users/";
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
	writerMessagesPidgin pidginMessages(config->outputFolder() + "//pidgin/messages.xml", "pidgin");
	writerMessagesPidgin pidginAccount(config->outputFolder() + "//pidgin/accounts.xml", "pidgin");
	writerMessagesPidgin pidginContacts(config->outputFolder() + "//pidgin/contacts.xml", "pidgin");
	if(!pidginMessages.opened()||!pidginAccount.opened()||!pidginContacts.opened())
	{
        std::cout << "Failed task :: Can't create output folder & files\n";
		return false;
	}

	QString name;
	QString email;
	QString protocol;
	QString password;

	QFile fileXmlAccount(config->inputFolder() + "/Users/Default/AppData/Roaming/.purple/accounts.xml");
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

	QFile fileXmlContacts(config->inputFolder() + "/Users/Default/AppData/Roaming/.purple/blist.xml");
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

	return true;
};

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskPidginWin());
}
