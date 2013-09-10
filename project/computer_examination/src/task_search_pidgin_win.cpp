#include "task_search_pidgin_win.h"
#include <iostream>

taskSearchPidginWin::taskSearchPidginWin()
{
	m_strName = "Search Pidgin (Win)";
	m_strDescription = "Task is search logs of Pidgin for Windows";
};

bool taskSearchPidginWin::supportOS(const coex::typeOS &os)
{
	return ((os == coex::ceWindowsXP) || (os == coex::ceWindows7));
};

QString taskSearchPidginWin::name()
{
	return m_strName;
};

QString taskSearchPidginWin::description()
{
	return m_strDescription;
};

bool taskSearchPidginWin::test()
{
	// unit test
	return true;
};

bool taskSearchPidginWin::execute(const coex::config &config)
{
  // TODO: 
	std::cout << ">>>>>> same execute...\n\n";
	std::cout << config.inputFolder.toStdString() << "\n";
	std::cout << config.outputFolder.toStdString() << "\n";
	
	return true;
};
		
