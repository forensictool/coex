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
        if ((entry == ".") || (entry == ".."))
            continue;

        QFileInfo info = list.at(i);
        std::cout << qPrintable(QString("%1").arg(info.fileName())) << std::endl;
    };  
};
/*
QDirIterator dirIt("/folder_path",QDirIterator::Subdirectories);
while (dirIt.hasNext()) {
    dirIt.next();
    if (QFileInfo(dirIt.filePath()).isFile())
        if (QFileInfo(dirIt.filePath()).suffix() == "txt")
            qDebug()<<dirIt.filePath();
}
*/


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
    if(m_bDebug)
        std::cout << "  !!! debug mode on.\n";


    return true;
}


		
