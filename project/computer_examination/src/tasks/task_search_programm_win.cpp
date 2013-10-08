#include "task_search_programm_win.h"
#include <iostream>
#include <QDir>
#include <QDirIterator>

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
            dirStr += "/Program Files/";
            std::cout << dirStr.toStdString() << std::endl;
            QDirIterator dirit(dirStr, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
            QStringList dirList;
            while(dirit.hasNext())
            {
                QString str = QString("%1").arg(dirit.next());
                dirList << str; //collect all parts for files in dolder
                QStringList buf = str.split("Program Files", QString::SkipEmptyParts);
                buf = buf.at(1).split("/", QString::SkipEmptyParts);
                str = buf[0];
                if(!programFiles->contains(str))
                {
                    *programFiles << str;
                    //std::cout << programFiles->at(programFiles->size() - 1).toStdString() << std::endl; //for tests
                }
            }

            std::cout << std::endl << std::endl;
            for (int i = 0; i < dirList.size(); i++)
                std::cout << programFiles->at(i).toStdString() << std::endl;
            break;            
        }
        default:
            std::cout << "Unknown system =(" << std::endl;
            break;
    }
    delete programFiles;

    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
	return true;
}
		
