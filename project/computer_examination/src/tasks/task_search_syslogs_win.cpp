#include "task_search_syslogs_win.h"
#include <iostream>

taskSearchSyslogsWin::taskSearchSyslogsWin()
{
	m_strName = "taskSearchSyslogsWin";
	m_strDescription = " It 's example task";
};

bool taskSearchSyslogsWin::supportOS(const coex::typeOS &os)
{
	if(os == coex::ceWindowsXP)
		return true;
	return false;
};

QString taskSearchSyslogsWin::name()
{
	return m_strName;
};

QString taskSearchSyslogsWin::description()
{
	return m_strDescription;
};

bool taskSearchSyslogsWin::test()
{
	// unit test
	return true;
};

bool taskSearchSyslogsWin::execute(const coex::config &config)
{
	std::cout << ">>>>>> same execute...\n\n";
	return true;
};
		
