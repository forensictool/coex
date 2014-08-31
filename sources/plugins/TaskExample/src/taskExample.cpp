#include "taskExample.h"

#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>

TaskExample::TaskExample() {
	m_bDebug = false;
};

QString TaskExample::help() {
	return "\t--debug - viewing debug messages";
};

QString TaskExample::name() {
	return "example";
};

QString TaskExample::author() {
	return "Evgenii Sopov";
};

QString TaskExample::description() {
	return "example task";
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

	// some processing

	return true;
};

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskExample());
}
