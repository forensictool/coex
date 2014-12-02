#include "taskMessengers.h"
#include "XMLReader_ICQContacts.h"
#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>

TaskMessengers::TaskMessengers() {
	m_bDebug = false;
};

QString TaskMessengers::help() {
	return "\t--debug - viewing debug messages";
};

QString TaskMessengers::name() {
	return "ICQ";
};

QString TaskMessengers::author() {
	return "Marina Meyta";
};

QString TaskMessengers::description() {
	return "messengers task";
};

bool TaskMessengers::isSupportOS(const coex::ITypeOperationSystem *os) {
	return (os->platform() == "Windows");
};

void TaskMessengers::setOption(QStringList options) {
	/*
	 * 
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};

bool TaskMessengers::execute(const coex::IConfig *config) {
	if(m_bDebug) {
		std::cout << "  !!! debug mode on.\n";
		std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
	};

    XMLReader_ICQContacts reader; // создаем экземпляр класса
    reader.read("/home/marina/gpo/coex/tmp/test-data/Windows7_Ult/Users/Default/AppData/Roaming/test.xml", config->outputFolder());

	return true;
};

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskMessengers());
}
