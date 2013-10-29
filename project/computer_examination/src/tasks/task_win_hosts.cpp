#include "task_search_syslogs_win.h"
#include <iostream>
#include <QString>
#include <QDir>
#include <QDirIterator>

taskSearchHosts::taskSearchHosts()
{
    m_strName = "Search Hosts (Win)";
    m_strDescription = " It's task searching file 'hosts' in WinOs";
    m_bDebug = false;
}

taskSearchHosts::~taskSearchHosts(){}

QString taskSearchHosts::manual()
{
	return "\t--debug - viewing debug messages";
}

void taskSearchHosts::setOption(QStringList options)
{
    if(options.contains("--debug"))
        m_bDebug = true;
}

QString taskSearchHosts::command()
{
	return "ghosts";
}

bool taskSearchHosts::supportOS(const coex::typeOS &os)
{
	if(os == coex::ceWindowsXP || coex::ceWindows7 || coex::ceWindows8)
		return true;
	return false;
}

QString taskSearchHosts::name()
{
	return m_strName;
}

QString taskSearchHosts::description()
{
	return m_strDescription;
}

bool taskSearchHosts::test()
{
	// unit test
	return true;
}

QString taskSearchHosts::findFileHosts(QString dir)
{
    QDir dir(dirStr);  //open this folder and create filters
    dir.setFilter(QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList(); //create list with files in folder
    for (int i = 0; i < list.size(); i++)
    {
        QFileInfo info = list.at(i);
        std::cout << qPrintable(QString("%1").arg(info.fileName())) << std::endl;
    };  
};

/*void ListDirRecursive(QString directory)
{
    QDir dir(directory);
    foreach(QString entry, dir.entryList())
    {
        if ((entry == ".") || (entry == ".."))
            continue;
        QDir subdir = QDir(dir.absoluteFilePath(entry));
        if (subdir.exists())
            ListDirRecursive(subdir.absolutePath());
        qDebug() << subdir.absolutePath();
    }
}
*/


bool taskSearchHosts::execute(const coex::config& config)
{
    //std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;

    if(m_bDebug)
        std::cout << "  !!! debug mode on.\n";

    QString fileName = findFileHosts(config.inputFolder);


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

    readLogFiles(*logFiles, config);
    delete logFiles;

    readEvtFiles(*evtFiles, config);
    delete evtFiles;

    //std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    return true;
}


		
