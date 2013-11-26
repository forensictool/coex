#include "task_search_skype_win.h"
#include <iostream>
#include <QDir>
#include <QDirIterator>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QtSql/QSqlDatabase>
#include <QRegExp>
#include <QTextStream>
#include <QDebug>

taskSearchSkypeWin::taskSearchSkypeWin()
{
	m_strName = "Search Skype (Win)";
	m_strDescription = "Task is search logs of Skype for WINDOWS";
	m_bDebug = false;
};

QString taskSearchSkypeWin::manual()
{
	return "\t--debug - viewing debug messages";
};

void taskSearchSkypeWin::setOption(QStringList options)
{
	if(options.contains("--debug"))
		m_bDebug = true;
};

QString taskSearchSkypeWin::command()
{
	return "skype";
};

bool taskSearchSkypeWin::supportOS(const coex::typeOS &os)
{
	return ((os == coex::ceWindowsXP) || (os == coex::ceWindows7));
};

QString taskSearchSkypeWin::name()
{
	return m_strName;
};

QString taskSearchSkypeWin::description()
{
	return m_strDescription;
};

bool taskSearchSkypeWin::test()
{
	// unit test
	return true;
};

bool taskSearchSkypeWin::execute(const coex::config &config)
{
	// example usage options
	if(m_bDebug)
		std::cout << "  !!! debug mode on.\n";

	{
		QDir dir(config.outputFolder);
		dir.mkdir("skype");
	}
	
	QFile fileXML(config.outputFolder + "//skype/messages.xml");
	// open a file
	if (!fileXML.open(QIODevice::WriteOnly))
	{
		std::cout << " failed task\n";
		return false;
	}
	QXmlStreamWriter* xmlWriter = new QXmlStreamWriter();

	xmlWriter->setDevice(&fileXML);
	xmlWriter->setAutoFormatting(true);
	xmlWriter->writeStartDocument();
	xmlWriter->writeStartElement("Messages");
			
  // TODO: 
	
	if(m_bDebug)
	  std::cout << "===========================================\n\n";
	// std::cout << config.inputFolder.toStdString() << "\n";
	// std::cout << config.outputFolder.toStdString() << "\n";

    QString path = config.inputFolder + "/Users/fox/AppData/Roaming/Skype";

    path = path + "/fox.user.3/main.db"; //hard code ... or not

/*
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if( !db.open() )
    {
      qDebug() << db.lastError();
      qFatal( "Failed to connect." );
    }

      qDebug( "Connected!" );

*/
    if(m_bDebug)
      std::cout << "===========================================\n\n";	
    
    return true;
};
		
