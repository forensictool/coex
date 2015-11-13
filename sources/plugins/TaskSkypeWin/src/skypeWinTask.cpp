#include "skypeWinTask.h"
#include "writerMessagesSkype.h"

TaskSkypeWin::TaskSkypeWin() {
	m_bDebug = false;
};

QString TaskSkypeWin::help() {
	return "\t--debug - viewing debug messages";
};

QString TaskSkypeWin::name() {
	return "SkypeWin";
};

QString TaskSkypeWin::author() {
	return "Igor Polyakov";
};

QString TaskSkypeWin::description() {
	return "Task is search logs of Skype for WINDOWS";
};

bool TaskSkypeWin::isSupportOS(const coex::ITypeOperationSystem *os) {
    return (os->platform() == "Windows" && (os->version() == "XP" || os->version() == "7" || os->version() == "8"));
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
    if (m_bDebug) {
        qDebug() << "===============TaskSkypeWin================\n\n";
        qDebug() << "Debug mode ON\n";
        qDebug() << "InputFolder: " << config->inputFolder() << "\n";
    };

    QDir dir(config->outputFolder());
    dir.mkdir("skype");

	QString path = config->inputFolder() + "/Users/";
	QStringList  listOfSkypeUser;

    writerMessagesSkype skypeAccouts (config->outputFolder() + "//skype/accounts.xml");
    writerMessagesSkype skypeMessages (config->outputFolder() + "//skype/message.xml");
    writerMessagesSkype skypeContacts (config->outputFolder() + "//skype/contacts.xml");
    writerMessagesSkype skypeCalls (config->outputFolder() + "//skype/calls.xml");
    if(!skypeMessages.opened()||!skypeContacts.opened()||!skypeAccouts.opened()||!skypeCalls.opened())
    {
        qDebug() << "Failed task :: Can't create output folder & files\n";
        return false;
    }
	QRegExp skypePathLog(".*Skype.*main.db");
	QDirIterator dirPath (path, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);


	while(dirPath.hasNext())
	{
		if (dirPath.next().contains(skypePathLog))
		{
			QString qwerty = skypePathLog.cap(0);
            if(m_bDebug)
                std::cout << "\n :: " <<qwerty.toStdString();
			listOfSkypeUser << skypePathLog.cap(0);

            path = dirPath.filePath();
            if(!QFile::exists(path))
                return false;
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "skype_sqlite_db");
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
            QString sql = "select skypename, fullName, emails, ipcountry from  Accounts;";
            QSqlQuery query(db);

            if (query.exec(sql) != false) {
                while (query.next())
                {
                    QSqlRecord rec = query.record();
                    QString skypename = query.value(rec.indexOf("skypename")).toString();
                    QString fullName = query.value(rec.indexOf("fullName")).toString();
                    QString emails = query.value(rec.indexOf("emails")).toString();
                    QString ipcountry = query.value(rec.indexOf("ipcountry")).toString();
                    skypeAccouts.writeInfo(skypename,fullName,emails,ipcountry);
                }
            }
            else {
                if(m_bDebug)
                    qDebug() << query.lastError().text();
            }
            sql = "select skypename, fullName, birthday, gender, phone_mobile, languages, country, city from Contacts";
            if (query.exec(sql) != false) {
                while (query.next())
                {
                    QSqlRecord rec = query.record();
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
            } else {
                if(m_bDebug)
                    qDebug() << query.lastError().text();
            }
            sql = "select author, timestamp, body_xml from Messages;";
            query.exec(sql);
            if (query.exec(sql) != false)
            {
                while (query.next())
                {
                    QSqlRecord rec = query.record();
                    QString author = query.value(rec.indexOf("author")).toString();
                    QString timestamp = query.value(rec.indexOf("timestamp")).toString();
                    //QDateTime::fromTime_t(x);
                    QString body_xml = query.value(rec.indexOf("body_xml")).toString();

                    skypeMessages.writeMessage(author,timestamp,body_xml);
                }
            } else {
                if(m_bDebug)
                    qDebug() << query.lastError().text();
            }
            sql = "select begin_timestamp, duration, host_identity, current_video_audience from Calls;";
            query.exec(sql);
            if (query.exec(sql) != false) {
                while (query.next())
                {
                    QSqlRecord rec = query.record();
                    QString begin_timestamp = query.value(rec.indexOf("begin_timestamp")).toString();
                    QString duration = query.value(rec.indexOf("duration")).toString();
                    QString host_identity = query.value(rec.indexOf("host_identity")).toString();
                    QString current_video_audience = query.value(rec.indexOf("current_video_audience")).toString();
                    skypeCalls.writeCalls(begin_timestamp,duration,host_identity,current_video_audience);
                }
            } else {
                if(m_bDebug)
                    qDebug() << query.lastError().text();
            }
        }
	}
    return true;
}

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskSkypeWin());
}
