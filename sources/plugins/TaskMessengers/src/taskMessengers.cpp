#include "taskMessengers.h"

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
	return "messengers";
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

	std:: cout << "hello"; 
	// some processing

	return true;
};

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskMessengers());
}
