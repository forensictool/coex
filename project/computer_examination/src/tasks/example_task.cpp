#include "example_task.h"
#include <iostream>

exampleTask::exampleTask()
{
	m_strName = "exampleTask";
	m_strDescription = " It 's example task";
};

bool exampleTask::supportOS(const coex::typeOS &os)
{
	if(os == coex::ceWindowsXP)
		return true;
	return false;
};

QString exampleTask::name()
{
	return m_strName;
};

QString exampleTask::description()
{
	return m_strDescription;
};

bool exampleTask::test()
{
	// unit test
	return true;
};

bool exampleTask::execute(const coex::config &config)
{
	std::cout << ">>>>>> same execute...\n\n";
	return true;
};
		
