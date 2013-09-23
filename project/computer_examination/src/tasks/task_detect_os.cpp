#include "task_detect_os.h"
#include <iostream>

taskDetectOs::taskDetectOs()
{
	m_strName = "taskDetectOs";
	m_strDescription = " It 's example task";
};

bool taskDetectOs::supportOS(const coex::typeOS &os)
{
	if(os == coex::ceWindowsXP)
		return true;
	return false;
};

QString taskDetectOs::name()
{
	return m_strName;
};

QString taskDetectOs::description()
{
	return m_strDescription;
};

bool taskDetectOs::test()
{
	// unit test
	return true;
};

bool taskDetectOs::execute(const coex::config &config)
{
	std::cout << ">>>>>> same execute...\n\n";
	return true;
};
		
