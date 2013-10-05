#include "task_search_pidgin_unix.h"
#include <iostream>

taskSearchPidginUnix::taskSearchPidginUnix()
{
	m_strName = "Search Pidgin (Unix)";
	m_strDescription = "Task is search logs of Pidgin for Unix/Linux";
};

QString taskSearchPidginUnix::manual()
{
	return "\t--debug - viewing debug messages";
};

void taskSearchPidginUnix::setOption(QStringList)
{
	
};

QString taskSearchPidginUnix::command()
{
	return "pidgin";
};

bool taskSearchPidginUnix::supportOS(const coex::typeOS &os)
{
	return (os == coex::ceLinux);
};

QString taskSearchPidginUnix::name()
{
	return m_strName;
};

QString taskSearchPidginUnix::description()
{
	return m_strDescription;
};

bool taskSearchPidginUnix::test()
{
	// unit test
	return true;
};

bool taskSearchPidginUnix::execute(const coex::config &config)
{
  // TODO: 
	std::cout << ">>>>>> same execute...\n\n";
	std::cout << config.inputFolder.toStdString() << "\n";
	std::cout << config.outputFolder.toStdString() << "\n";
	
	return true;
};
		
