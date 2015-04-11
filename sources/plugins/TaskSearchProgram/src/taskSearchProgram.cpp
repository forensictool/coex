#include "taskSearchProgram.h"

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
    return "Search Program";//
};

QString TaskExample::author() {
    return "-----";//
};

QString TaskExample::description() {
    return "example task";//
};

bool TaskExample::isSupportOS(const coex::ITypeOperationSystem *os) {
    return (os->platform() == "Windows" && (os->version() == "XP" || os->version() == "7" || os->version() == "8"));
};

void TaskExample::setOption(QStringList options) {
	/*
	 * 
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};

//здесь функционал


bool TaskExample::execute(const coex::IConfig *config) {
	if(m_bDebug) {
		std::cout << "  !!! debug mode on.\n";
		std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
	};

    //main

	return true;
};

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskExample());
}
