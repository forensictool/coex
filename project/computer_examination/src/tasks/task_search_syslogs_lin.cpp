#include "task_search_syslogs_lin.h"
#include <iostream>

taskSearchSyslogsLin::taskSearchSyslogsLin()
{
	m_strName = "taskSearchSyslogsLin";
	m_strDescription = " It 's example task";
};

QString taskSearchSyslogsLin::manual()
{
	return "\t--debug - viewing debug messages";
};

void taskSearchSyslogsLin::setOption(QStringList)
{
	
};

QString taskSearchSyslogsLin::command()
{
	return "syslogs";
};

bool taskSearchSyslogsLin::supportOS(const coex::typeOS &os)
{
	if(os == coex::ceLinux)
		return true;
	return false;
};

QString taskSearchSyslogsLin::name()
{
	return m_strName;
};

QString taskSearchSyslogsLin::description()
{
	return m_strDescription;
};

bool taskSearchSyslogsLin::test()
{
	// unit test
	return true;
};

bool taskSearchSyslogsLin::execute(const coex::config &/*config*/)
{
	std::cout << ">>>>>> same execute...\n\n";
	return true;
};
		
