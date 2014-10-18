#include "taskFirefox.h"

#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

TaskExample::TaskExample() {
	m_bDebug = false;
};

QString TaskExample::help() {
	return "\t--debug - viewing debug messages";
};

QString TaskExample::name() {
    return "firefox-win";
};

QString TaskExample::author() {
    return "Rachkovan Oleg";
};

QString TaskExample::description() {
    return "search file db";
};

bool TaskExample::isSupportOS(const coex::ITypeOperationSystem *os) {
	return (os->platform() == "Windows");
};

void TaskExample::setOption(QStringList options) {
	/*
	 * 
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};

bool TaskExample::execute(const coex::IConfig *config) {
	if(m_bDebug) {
		std::cout << "  !!! debug mode on.\n";
		std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
    };

    QString path = config->inputFolder() + "/Users/";
    QDir dir(path);
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList users = dir.entryInfoList();
    QStringList foundFile;
    for( int i = 0; i < users.size(); i++)
    {
        QFileInfo fileInfo = users.at(i);
        path = fileInfo.absoluteFilePath() + "/AppData/Roaming/Mozilla/";
        QDirIterator dirPath (path, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
        while(dirPath.hasNext())
        {
            QFileInfo fileInfo = dirPath.next();
            if (fileInfo.fileName() == "places.sqlite")
                foundFile << fileInfo.absoluteFilePath();
        }
    }

    for (int i = 0; i < foundFile.size(); i++)
    {
        if( !QFile::exists(foundFile.at(i)) )
            return false;

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName( foundFile.at(i) );

        if( !db.open() )
            if(true)
                std::cout << "Not connected with this db" << foundFile.at(i).toStdString() <<  "\n\n";

        QString sql;
        QSqlQuery query(db);
        QSqlRecord rec = query.record();
        sql = "select *  from sqlite_master;";// for each table from sqlite_master output *
        query.exec(sql);
        rec = query.record();
        std::cout << "\nFOR " << foundFile.at(i).toStdString() << "\n\n";
        while( query.next() )
        {
            int id = query.value(0).toInt();
            QString content = query.value(4).toString();
            std::cout << id << ": " << content.toStdString() << "\n\n";
        }
        db.close();
    }

	return true;
};

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskExample());
}
