#include "task.h"

#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>

TaskChromeWin::TaskChromeWin() {
	m_bDebug = false;
};

QString TaskChromeWin::help() {
	return "\t--debug - viewing debug messages";
};

QString TaskChromeWin::name() {
	return "ChromeWin";
};

QString TaskChromeWin::author() {
	return "Vladislav Shipovskoi";
};

QString TaskChromeWin::description() {
	return "ChromeWin";
};

bool TaskChromeWin::isSupportOS(const coex::ITypeOperationSystem *os) {
	return (os->platform() == "Windows");
};

void TaskChromeWin::setOption(QStringList options) {
	/*
	 * 
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};

bool TaskChromeWin::execute(const coex::IConfig *config) {
	if(m_bDebug) {
		std::cout << "  !!! debug mode on.\n";
		std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
	};

	// some processing

	return true;
};

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskChromeWin());
}
