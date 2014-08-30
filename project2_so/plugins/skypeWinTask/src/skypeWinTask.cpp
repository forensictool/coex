#include "skypeWinTask.h"

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

QString getLibName()
{
	return(QString("skypeWinTask"));
}

bool m_bDebug = true;

bool execute(const coex::config& config)
{
	// example usage options
	if(m_bDebug)
	std::cout << "  !!! debug mode on.\n";
	{
		QDir dir(config.outputFolder);
		dir.mkdir("skype");
	}
	
	// TODO: 
	
	if(m_bDebug)
	std::cout << "===========================================\n\n";
	// std::cout << config.inputFolder.toStdString() << "\n";
	// std::cout << config.outputFolder.toStdString() << "\n";
	QString path = config.inputFolder + "/Users/";
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
	writerMessagesSkype skypeAccouts (config.outputFolder + "//skype/accounts.xml", "Accounts", "skype");
	writerMessagesSkype skypeMessages (config.outputFolder + "//skype/message.xml", "Messages", "skype");
	writerMessagesSkype skypeContacts (config.outputFolder + "//skype/contacts.xml", "Contacts", "skype");
	writerMessagesSkype skypeCalls (config.outputFolder + "//skype/calls.xml", "Calls", "skype");
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
    QString fileType,
    QString type,
    QString messangerName
)
{
    m_bOpened = true;
    m_pFile= new QFile(fileType);
    if (!m_pFile->open(QIODevice::Append))
    {
        m_bOpened = false;
        return;
    }
    m_pXmlWriter= new QXmlStreamWriter();
    m_pXmlWriter->setDevice(m_pFile);
    m_pXmlWriter->setAutoFormatting(true);
    m_pXmlWriter->writeStartDocument();
    m_pXmlWriter->writeStartElement(type);
    m_pXmlWriter->writeAttribute("Messenger" ,messangerName);
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
    m_pXmlWriter->writeStartElement("message");
    m_pXmlWriter->writeAttribute("author" ,author);
    m_pXmlWriter->writeAttribute("timestamp" ,timestamp);
    m_pXmlWriter->writeAttribute("body_xml" ,body_xml);
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
    m_pXmlWriter->writeStartElement("message");

    bool isconverted;
    uint iunixtime_integer = begin_timestamp .toUInt(&isconverted);
    QString idatetime = QDateTime::fromTime_t(iunixtime_integer).toString();

    m_pXmlWriter->writeAttribute("begin_timestamp" ,idatetime);
    m_pXmlWriter->writeAttribute("duration" ,duration);
    m_pXmlWriter->writeAttribute("host_identity" ,host_identity);
    m_pXmlWriter->writeAttribute("current_video_audience" ,current_video_audience);
    m_pXmlWriter->writeEndElement();
};

// like skype contact
void writerMessagesSkype::writeContacts(
        QString skypename ,
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
    m_pXmlWriter->writeStartElement("contact");
    m_pXmlWriter->writeAttribute("skypeName" ,skypename);
    m_pXmlWriter->writeAttribute("fullName" ,fullName);
    m_pXmlWriter->writeAttribute("birthday" ,birthday);
    if (gender == "1")
        gender = "Male";
    else if (gender == "2")
        gender = "Felmale";
    else
        gender = "Unknow";
    m_pXmlWriter->writeAttribute("gender" ,gender);
    m_pXmlWriter->writeAttribute("phone_mobile" ,phone_mobile);
    if (languages == "ru")
        languages = "Russain";
    else if (languages == "en")
        languages = "English";
    else
        languages = "Other";
    m_pXmlWriter->writeAttribute("languages" ,languages);
    if (country == "ru")
        country = "Russia";
    else if (country == "en")
        country = "English/USA";
    else
        country = "Other";
    m_pXmlWriter->writeAttribute("country" ,country);
    m_pXmlWriter->writeAttribute("city" ,city);
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
    m_pXmlWriter->writeStartElement("info_account");
    m_pXmlWriter->writeAttribute("skypeName" ,skypeName);
    m_pXmlWriter->writeAttribute("fullName" ,fullName);
    m_pXmlWriter->writeAttribute("emails" ,emails);
    m_pXmlWriter->writeAttribute("ipcountry" ,ipcountry);
    m_pXmlWriter->writeEndElement();
};
