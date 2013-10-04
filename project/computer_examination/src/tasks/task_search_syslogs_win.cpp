#include "task_search_syslogs_win.h"
#include <iostream>
#include <QString>
#include <QDir>
#include <QDirIterator>
taskSearchSyslogsWin::taskSearchSyslogsWin()
{
	m_strName = "taskSearchSyslogsWin";
    m_strDescription = " It's task searchin logs for WinOs";
};

QString taskSearchSyslogsWin::manual()
{
	return "\t--debug - viewing debug messages";
};

void taskSearchSyslogsWin::setOption(QStringList)
{
	
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

bool taskSearchSyslogsWin::execute(const coex::config &config)
{
    switch(config.os)
    {
    case coex::ceWindowsXP:
        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
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
        QStringList logEvtFiles;
        QDirIterator dirit(dirStr, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
        while(dirit.hasNext())
        {
            QString str = QString("%1").arg(dirit.next());
            QStringList buf = str.split("/", QString::SkipEmptyParts);
            buf = buf.at(buf.size() - 1).split(".", QString::SkipEmptyParts);
            if ((buf.at(buf.size() - 1).toLower() == "log") | (buf.at(buf.size() - 1).toLower() == "evt"))
            {
                logEvtFiles << str;
            }
        }
        QDir(config.outputFolder).mkdir("LOGS"); //создаем диррикторию в выходном каталоге
        QString outFolder = config.outputFolder + "/LOGS/";
        for(int i = 0; i < logEvtFiles.size(); i++)
        {
            QStringList list = logEvtFiles.at(i).split("/", QString::SkipEmptyParts);
            QFile::copy(logEvtFiles.at(i), outFolder + list.at(list.size() - 1));
        }
        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
        return true;
    break;
    }
};
		
