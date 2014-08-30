#include "task_search_syslogs_win.h"
#include <iostream>
#include <QString>
#include <QDir>
#include <QDirIterator>

#include "../winEventReader/evtReader.h"

taskSearchSyslogsWin::taskSearchSyslogsWin()
{
    m_strName = "Search Syslogs (Win)";
    m_strDescription = " It's task searchin logs for WinOs";
    m_bDebug = false;
}

taskSearchSyslogsWin::~taskSearchSyslogsWin(){}

QString taskSearchSyslogsWin::manual()
{
	return "\t--debug - viewing debug messages";
}

void taskSearchSyslogsWin::setOption(QStringList options)
{
    if(options.contains("--debug"))
        m_bDebug = true;
}

QString taskSearchSyslogsWin::command()
{
	return "syslogs";
}

bool taskSearchSyslogsWin::supportOS(const coex::typeOS &os)
{
	if(os == coex::ceWindowsXP)
		return true;
	return false;
}

QString taskSearchSyslogsWin::name()
{
	return m_strName;
}

QString taskSearchSyslogsWin::description()
{
	return m_strDescription;
}

bool taskSearchSyslogsWin::test()
{
	// unit test
	return true;
}

/*void taskSearchSyslogsWin::readLogFiles(QStringList logFiles, const coex::config &config)
{
    QDir(config.outputFolder).mkdir("SYSWINLOGS"); //создаем диррикторию в выходном каталоге
    QString outFolder = config.outputFolder + "/SYSWINLOGS/";

    // output logfiles list in outputfolder //

    for(int i = 0; i < logFiles.size(); i++)
    {
        QStringList list = logFiles.at(i).split("/", QString::SkipEmptyParts);
        QFile::copy(logFiles.at(i), outFolder + list.at(list.size() - 1));
    }
}*/

void taskSearchSyslogsWin::readEvtFiles(QStringList evtFiles, const coex::config &config)
{
    try
    {
        QDir(config.outputFolder).mkdir("SYSWINEVTS");
    }
    catch(...)
    {
        if(m_bDebug)
            std::cout << "SYSWINEVT dir is not created" << std::endl;
        return;
    }

    QString outFolder = config.outputFolder + "/SYSWINEVTS/";
    for(int i = 0; i < evtFiles.size(); i++)
    {
        QStringList list = evtFiles.at(i).split("/", QString::SkipEmptyParts);
        //QFile::copy(evtFiles.at(i), outFolder + list.at(list.size() - 1));

		if(m_bDebug)
			std::cout << "-----------------------------------------------------" << std::endl;
			
        try
        {
            winEventLog log(evtFiles.at(i), outFolder + list.at(list.size() - 1) + ".xml");
            log.read();
        }
        catch(...)
        {
            if(m_bDebug)
                std::cout << "Error in " + evtFiles.at(i).toStdString() + " file" << std::endl;
            continue;
        }
    }
}



/* 
 * also look here for *.Evt files
 * 
 * http://www.whitehats.ca/main/members/Malik/malik_eventlogs/malik_eventlogs.html
 * 
 * and in thirdparty/grokevt (python scripts)
 */

bool taskSearchSyslogsWin::execute(const coex::config& config)
{
	if(m_bDebug)
      std::cout << "!!!>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;

    if(m_bDebug)
        std::cout << "  !!! debug mode on.\n";

    //QStringList* logFiles = new QStringList();
    QStringList* evtFiles = new QStringList();

    switch(config.os)
    {
        case coex::ceWindowsXP:
        {
            QString dirStr(config.inputFolder);
            dirStr += "/WINDOWS";
            QDirIterator dirit(dirStr, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

            try
            {
                while(dirit.hasNext())
                {
                    QString str = QString("%1").arg(dirit.next());
                    QStringList buf = str.split("/", QString::SkipEmptyParts);
                    buf = buf.at(buf.size() - 1).split(".", QString::SkipEmptyParts);
                    /*if (buf.at(buf.size() - 1).toLower() == "log")
                    {
                        *logFiles << str;
                    }*/
                    if (buf.at(buf.size() - 1).toLower() == "evt")
                    {
                        *evtFiles << str;
                    }
                }
            }
            catch(...)
            {
                if(m_bDebug) std::cout << "OOOOPS!" << std::endl;
            }

            break;
        }

        default:
        {
            std::cout << "Unknown system =(" << std::endl;
            break;
        }
    }

    //readLogFiles(*logFiles, config);
    //delete logFiles;

    readEvtFiles(*evtFiles, config);
    delete evtFiles;

	if(m_bDebug)
      std::cout << "!!!>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
      
    return true;
}


		
