#include "task_search_programm_win.h"
#include <iostream>

taskSearchProgrammWin::taskSearchProgrammWin()
{
	m_strName = "Search Programm (Win)";
	m_strDescription = "Task is search installed prgramms in Windows";
};

bool taskSearchProgrammWin::supportOS(const coex::typeOS &os)
{
	return ((os == coex::ceWindowsXP) || (os == coex::ceWindows7));
};

QString taskSearchProgrammWin::name()
{
	return m_strName;
};

QString taskSearchProgrammWin::description()
{
	return m_strDescription;
};

bool taskSearchProgrammWin::test()
{
	// unit test
	return true;
};

bool taskSearchProgrammWin::execute(const coex::config &config)
{
  // TODO: 
	std::cout << ">>>>>> same execute...\n\n";
	std::cout << config.inputFolder.toStdString() << "\n";
	std::cout << config.outputFolder.toStdString() << "\n";
	
	return true;
};
		
