#include "taskOutlook2007.h"
#include "writerMessages.h"
#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>

taskOutlook2007::taskOutlook2007() {
	m_bDebug = false;
};

QString taskOutlook2007::help() {
	return "\t--debug - viewing debug messages";
};

QString taskOutlook2007::name() {
    return "TaskOutlook2007";
};

QString taskOutlook2007::author() {
    return "Serakov Andrey";
};

QString taskOutlook2007::description() {
    return "TaskOutlook2007 task";
};

bool taskOutlook2007::isSupportOS(const coex::ITypeOperationSystem *os) {
	return (os->platform() == "Windows");
};

void taskOutlook2007::setOption(QStringList options) {
	/*
	 * 
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};

bool taskOutlook2007::execute(const coex::IConfig *config) {
	if(m_bDebug) {
		std::cout << "  !!! debug mode on.\n";
		std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
	};

    if(m_bDebug)
        std::cout << "  !!! debug mode on.\n";
        {
            QDir dir(config->outputFolder());
            dir.mkdir("OutLook");
        }

    if (m_bDebug)
   std::cout << "\n";

   QString path = config->inputFolder() + "/Users/";
   QDir dir(path);
   dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
   QFileInfoList users = dir.entryInfoList();
   QStringList foundFile;
   for( int i = 0; i < users.size();++i)
   {
       QFileInfo fileInfo = users.at(i);
       path = fileInfo.absoluteFilePath() + "/AppData/Local/Microsoft/OutLook";
       //pathDoc = fileInfo.absoluteFilePath() + "/AppData/";
       QDirIterator dirPath (path, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
       while(dirPath.hasNext())
      {
          QFileInfo fileInfo = dirPath.next();
          if (fileInfo.suffix() == "pab" || fileInfo.suffix() == "oab")
          {
              foundFile << fileInfo.absoluteFilePath();
          }
       }
   }

 writerMessagesPidgin OutLookAdres(config->outputFolder() + "//OutLook/Adresbook.xml", "OutLook");
 if(!OutLookAdres.opened())
 {
     std::cout << " failed task\n";
     return false;
 }














    // some processing

	return true;
};

coex::ITask* createTask() {
    return (coex::ITask*)(new taskOutlook2007());
}
