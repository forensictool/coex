#include "header.h"

// Another f#cking headers
#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>

TaskWinReg::TaskWinReg() {
	m_bDebug = false;
};

QString TaskWinReg::help() {
	return "\t--debug - viewing debug messages";
};

QString TaskWinReg::name() {
    return "RegWin";
};

QString TaskWinReg::author() {
    return "mrB4el";
};

QString TaskWinReg::description() {
    return "Task for converting Windows's register to .xml format";
};

bool TaskWinReg::isSupportOS(const coex::ITypeOperationSystem *os) {
    return (os->platform() == "Windows" && (os->version() == "7" || os->version() == "8")););
};

void TaskWinReg::setOption(QStringList options) {
	/*
	 * 
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};

bool TaskWinReg::execute(const coex::IConfig *config) {
	if(m_bDebug) {
		std::cout << "  !!! debug mode on.\n";
		std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
	};
    {
        QDir dir(config->outputFolder());
        dir.mkdir("register");
        dir.mkdir("register/sources");

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
    return (coex::ITask*)(new TaskWinReg());
}
