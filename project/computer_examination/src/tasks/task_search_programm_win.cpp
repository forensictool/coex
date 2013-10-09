#include "task_search_programm_win.h"
#include <iostream>
#include <QDir>
#include <QDirIterator>
#include <QTextStream>

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

QStringList taskSearchProgrammWin::getSubDirs(QString dirStr)
{
    QStringList dirList;
    QDirIterator dirit(dirStr, QDirIterator::Subdirectories);
    while(dirit.hasNext())
    {
        QString str = QString("%1").arg(dirit.next());
        QStringList buf = str.split(dirStr, QString::SkipEmptyParts);
        buf = buf.at(0).split("/", QString::SkipEmptyParts);
        if ((buf[0] == ".")|(buf[0] =="..")) continue;
        if (buf[0].split(".").size() != 1) continue;
        if (!dirList.contains(buf[0]))
        {
            dirList << buf[0];
        }
    }
    return dirList;
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
            *programFiles = getSubDirs(dirStr);
            QFile file(config.outputFolder+"/programs.txt");
            if(!file.open(QFile::WriteOnly | QFile::Text))
            {
                std::cout << "File not found" << std::endl;
                return false;
            }
            QTextStream fout(&file);
            for (int i = 0; i < programFiles->size(); i++)
            {
                fout << programFiles->at(i) << '\n';
                //std::cout << programFiles->at(i).toStdString() << std::endl;
                /*QStringList qsl = getSubDirs(dirStr + programFiles->at(i) + "/");
                for (int j = 0; j < qsl.size(); j++)
                    std::cout << qsl.at(j).toStdString() << std::endl;
                std::cout << std::endl;*/
            }
            file.flush();
            file.close();
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
		
