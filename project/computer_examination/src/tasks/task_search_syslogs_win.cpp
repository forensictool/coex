#include "task_search_syslogs_win.h"
#include <iostream>
#include <QString>
#include <QDir>
#include <QDirIterator>

taskSearchSyslogsWin::taskSearchSyslogsWin()
{
    m_strName = "Search Syslogs (Win)";
    m_strDescription = " It's task searchin logs for WinOs";
    m_bDebug = false;
};

QString taskSearchSyslogsWin::manual()
{
	return "\t--debug - viewing debug messages";
};

void taskSearchSyslogsWin::setOption(QStringList options)
{
    if(options.contains("--debug"))
        m_bDebug = true;
};

QString taskSearchSyslogsWin::command()
{
	return "syslogs";
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

/* 
 * also look here for *.Evt files
 * 
 * http://www.whitehats.ca/main/members/Malik/malik_eventlogs/malik_eventlogs.html
 * 
 * and in thirdparty/grokevt (python scripts)
 * */

bool taskSearchSyslogsWin::execute(const coex::config &config)
{
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;

    if(m_bDebug)
        std::cout << "  !!! debug mode on.\n";

    QStringList* logFiles = new QStringList();
    QStringList* evtFiles = new QStringList();

    switch(config.os)
    {
        case coex::ceWindowsXP:
        {
            //этот кусок кода находит все файлы типа *.log и *.evt в заданной дириктории
            /*QString dirStr(config.inputFolder);             //folder with logs
            dirStr += "/WINDOWS/system32/config";
            QDir dir(dirStr);                               //open this folder and create filters
            dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
            dir.setSorting(QDir::Size | QDir::Reversed);
            QStringList filters;
            filters << "*.log" << "*.evt";
            dir.setNameFilters(filters);
            QFileInfoList list = dir.entryInfoList();   //create list with files in folder
            for (int i = 0; i < list.size(); i++)
            {
                QFileInfo info = list.at(i);
                std::cout << qPrintable(QString("%1").arg(info.fileName())) << std::endl;
            }*/

            //этот кусок кода получает пути до всех *.log и *.evt файлов в дириктории (включая подкаталоги)
            QString dirStr(config.inputFolder);
            dirStr += "/WINDOWS";
            QDirIterator dirit(dirStr, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

            while(dirit.hasNext())
            {
                QString str = QString("%1").arg(dirit.next());
                QStringList buf = str.split("/", QString::SkipEmptyParts);
                buf = buf.at(buf.size() - 1).split(".", QString::SkipEmptyParts);
                if (buf.at(buf.size() - 1).toLower() == "log")
                {
                    *logFiles << str;
                }
                if (buf.at(buf.size() - 1).toLower() == "evt")
                {
                    *evtFiles << str;
                }
            }

            break;
        }

        default:
        {
            std::cout << "Unknown system =(" << std::endl;
            break;
        }
    }

    QDir(config.outputFolder).mkdir("SYSWINLOGS"); //создаем диррикторию в выходном каталоге
    QString outFolder = config.outputFolder + "/SYSWINLOGS/";
    for(int i = 0; i < logFiles->size(); i++)
    {
        QStringList list = logFiles->at(i).split("/", QString::SkipEmptyParts);
        QFile::copy(logFiles->at(i), outFolder + list.at(list.size() - 1));
    }
    delete logFiles;

    QDir(config.outputFolder).mkdir("SYSWINEVTS");
    outFolder = config.outputFolder + "/SYSWINEVTS/";
    for(int i = 0; i < evtFiles->size(); i++)
    {
        QStringList list = evtFiles->at(i).split("/", QString::SkipEmptyParts);
        QFile::copy(evtFiles->at(i), outFolder + list.at(list.size() - 1));
    }
    delete evtFiles;
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    return true;
}
		
