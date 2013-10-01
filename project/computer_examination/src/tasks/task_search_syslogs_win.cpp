#include "task_search_syslogs_win.h"
#include <iostream>
#include <QString>
#include <QDir>

taskSearchSyslogsWin::taskSearchSyslogsWin()
{
	m_strName = "taskSearchSyslogsWin";
    m_strDescription = " It's task searchin logs for WinOs";
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
    switch(config.os)
    {
    case coex::ceWindowsXP:
        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
        QString dirStr(config.inputFolder);             //folder with logs
        dirStr += "/WINDOWS/system32";
        QDir dir(dirStr);                               //open this folder and create filters
            dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
            dir.setSorting(QDir::Size | QDir::Reversed);
            QFileInfoList list = dir.entryInfoList();   //create list with files in folder
        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
        return true;
    break;
    }
};
		
