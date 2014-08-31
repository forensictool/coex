#include "skypeWinTask.h"
#include "writerMessages.h"

#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QSqlDatabase>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDateTime>

TaskSkypeWin::TaskSkypeWin() {
	m_bDebug = false;
};

QString TaskSkypeWin::help() {
	return "\t--debug - viewing debug messages";
};

QString TaskSkypeWin::name() {
	return "skype-win";
};

QString TaskSkypeWin::author() {
	return "Igor Polyakov";
};

QString TaskSkypeWin::description() {
	return "Task is search logs of Skype for WINDOWS";
};

bool TaskSkypeWin::isSupportOS(const coex::ITypeOperationSystem *os) {
	return (os->platform() == "Windows" && (os->version() == "XP" || os->version() == "7"));
};

void TaskSkypeWin::setOption(QStringList options) {
	/*
	 * 
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};

bool TaskSkypeWin::execute(const coex::IConfig *config) {
	// example usage options
	if(m_bDebug)
	std::cout << "  !!! debug mode on.\n";
	{
		QDir dir(config->outputFolder());
		dir.mkdir("skype");
	}
	
	// TODO: 
	
	if(m_bDebug)
		std::cout << "===========================================\n\n";
	// std::cout << config.inputFolder.toStdString() << "\n";
	// std::cout << config.outputFolder.toStdString() << "\n";
	QString path = config->inputFolder() + "/Users/";
	QStringList  listOfSkypeUser;
	QRegExp skypePathLog(".*Skype.*main.db");
	QDirIterator dirPath (path, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
	while(dirPath.hasNext())
	{
		if (dirPath.next().contains(skypePathLog))
		{
			QString qwerty = skypePathLog.cap(0);
			std::cout << "\n :: " <<qwerty.toStdString();
			listOfSkypeUser << skypePathLog.cap(0);
		}
	}
	writerMessagesSkype skypeAccouts (config->outputFolder() + "//skype/accounts.xml", "Accounts", "skype");
	writerMessagesSkype skypeMessages (config->outputFolder() + "//skype/message.xml", "Messages", "skype");
	writerMessagesSkype skypeContacts (config->outputFolder() + "//skype/contacts.xml", "Contacts", "skype");
	writerMessagesSkype skypeCalls (config->outputFolder() + "//skype/calls.xml", "Calls", "skype");
	if(!skypeMessages.opened()||!skypeContacts.opened()||!skypeAccouts.opened()||!skypeCalls.opened())
	{
		std::cout << " failed task\n";
		return false;
	}
	for(int i = 0; i < listOfSkypeUser.size(); i++)
	{
		path = listOfSkypeUser.at(i);
		if(!QFile::exists(path))
		return false;
		QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
		db.setDatabaseName(path);
		if( !db.open() )
		{
			if(m_bDebug)
			std::cout << "Not connected!" << /*db.lastError() <<*/ "\n\n";
		}
		if(m_bDebug)
		std::cout << "Connected!\n\n";
		/*QStringList listOfTables;
		listOfTables << "DbMeta" << "Contacts" << "LegacyMessages" <<  "Calls"
			<< "Accounts" << "Transfers" << "Voicemails" << "Chats"
			<< "Messages" << "ContactGroups" << "Videos" << "SMSes"
			<< "CallMembers" << "ChatMembers" << "Alerts" << "Conversations"
			<< "Participants" << "VideoMessages";*/
		QString sql;
		QSqlQuery query(db);
		//QString sql = "select skypename, fullname, languages, country, city  from " + strTableName + ";";
		QSqlRecord rec = query.record();
		sql = "select *  from  Accounts;";
		query.exec(sql);
		rec = query.record();
		while (query.next())
		{
			{
				QString strValue1 = query.value(rec.indexOf("skypename")).toString();
				QString strValue2 = query.value(rec.indexOf("fullName")).toString();
				QString strValue3 = query.value(rec.indexOf("emails")).toString();
				QString strValue4 = query.value(rec.indexOf("ipcountry")).toString();
				skypeAccouts.writeInfo(strValue1,strValue2,strValue3,strValue4);
			}
		}
		sql = "select *  from Contacts";
		query.exec(sql);
        rec = query.record();
		while (query.next())
		{
			{
                QString skypename = query.value(rec.indexOf("skypename")).toString();
                QString fullName = query.value(rec.indexOf("fullName")).toString();
                QString birthday = query.value(rec.indexOf("birthday")).toString();
                QString gender = query.value(rec.indexOf("gender")).toString();
                QString phone_mobile = query.value(rec.indexOf("phone_mobile")).toString();
                QString languages = query.value(rec.indexOf("languages")).toString();
                QString country = query.value(rec.indexOf("country")).toString();
                QString city = query.value(rec.indexOf("city")).toString();
                skypeContacts.writeContacts(skypename,fullName,birthday,gender,phone_mobile,languages,country,city);
			}
		}
		sql = "select *  from  Messages;";
		query.exec(sql);
		rec = query.record();
		while (query.next())
		{
			{
				QString strValue1 = query.value(rec.indexOf("author")).toString();
				QString strValue2 = query.value(rec.indexOf("timestamp")).toString();
                //QDateTime::fromTime_t(x);
				QString strValue3 = query.value(rec.indexOf("body_xml")).toString();
				skypeMessages.writeMessage(strValue1,strValue2,strValue3);
			}
		}
		sql = "select *  from  Calls;";
		query.exec(sql);
		rec = query.record();
		while (query.next())
		{
			{
                QString begin_timestamp = query.value(rec.indexOf("begin_timestamp")).toString();
                QString duration = query.value(rec.indexOf("duration")).toString();
                QString host_identity = query.value(rec.indexOf("host_identity")).toString();
                QString current_video_audience = query.value(rec.indexOf("current_video_audience")).toString();
                skypeCalls.writeCalls(begin_timestamp,duration,host_identity,current_video_audience);
			}
		}
	}
	if(m_bDebug)
	std::cout << "===========================================\n\n";	
	return true;
}

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskSkypeWin());
}
