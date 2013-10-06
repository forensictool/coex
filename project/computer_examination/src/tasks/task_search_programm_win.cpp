#include "task_search_programm_win.h"
#include <iostream>

taskSearchProgrammWin::taskSearchProgrammWin()
{
	m_strName = "Search Programm (Win)";
	m_strDescription = "Task is search installed prgramms in Windows";
    m_bDebug = false;
}

taskSearchProgrammWin::~taskSearchProgrammWin(){}

QString taskSearchProgrammWin::manual()
{
	return "\t--debug - viewing debug messages";
}

void taskSearchProgrammWin::setOption(QStringList options)
{
    if (options.contains("--debug"))
            m_bDebug = true;
}

QString taskSearchProgrammWin::command()
{
	return "programs";
}

bool taskSearchProgrammWin::supportOS(const coex::typeOS &os)
{
	return ((os == coex::ceWindowsXP) || (os == coex::ceWindows7));
}

QString taskSearchProgrammWin::name()
{
	return m_strName;
}

QString taskSearchProgrammWin::description()
{
	return m_strDescription;
}

bool taskSearchProgrammWin::test()
{
	// unit test
	return true;
}

bool taskSearchProgrammWin::execute(const coex::config &config)
{ 
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    QStringList *programFiles = new QStringList();

    switch (config.os)
    {
        case coex::ceWindowsXP:
        {
            QString dirStr(config.inputFolder);
            dirStr += "/Program";
            break;
        }
        default:
            break;
    }
    delete programFiles;

    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
	return true;
}
		
