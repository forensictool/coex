#include "taskWinReg.h"
#include "writerMessages.h"
#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QList>
#include <fstream>
#include <QTextStream>
#include <QByteArrayMatcher>



taskWinReg::taskWinReg() {
	m_bDebug = false;
};

QString taskWinReg::help() {
	return "\t--debug - viewing debug messages";
};

QString taskWinReg::name() {
    return "WinReg";
};

QString taskWinReg::author() {
    return "Lobanov Oleg";
};

QString taskWinReg::description() {
    return "taskWinReg task";
};

bool taskWinReg::isSupportOS(const coex::ITypeOperationSystem *os) {
	return (os->platform() == "Windows");
};

void taskWinReg::setOption(QStringList options) {
	/*
	 * 
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};


bool taskWinReg::execute(const coex::IConfig *config) {
	if(m_bDebug) {
		std::cout << "  !!! debug mode on.\n";
		std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
	};

   if(m_bDebug) std::cout << "  !!! debug mode on.\n";
   {
       QDir dir(config->outputFolder());
       dir.mkdir("WinReg");
   }

   if (m_bDebug)
   std::cout << "\n";



writerMessagesPidgin OutLookAdres(config->outputFolder() + "//OutLook/Adresbook.xml", "OutLook");
 if(!OutLookAdres.opened())
 {
     std::cout << " failed task\n";
     return false;
 }
	return true;
};

coex::ITask* createTask() {
    return (coex::ITask*)(new taskWinReg());
}
