#include "task_search_pidgin_win.h"
#include <iostream>

taskSearchPidginWin::taskSearchPidginWin()
{
	m_strName = "Search Pidgin (Win)";
	m_strDescription = "Task is search logs of Pidgin for Windows";
};

bool taskSearchPidginWin::supportOS(const coex::typeOS &os)
{
	return (os == coex::ceWindowsXP) || 
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

bool taskSearchPidgin::execute(const coex::config &config)
{
  // TODO: 
	std::cout << ">>>>>> same execute...\n\n";
	return true;
};
		
