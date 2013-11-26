#include "task_search_programm_win.h"
#include <iostream>
#include <QString>
#include <QDir>
#include <QDirIterator>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

taskSearchProgrammWin::taskSearchProgrammWin()
{
	m_strName = "Search Programm (Win)";
	m_strDescription = "Task is search installed prgramms in Windows";
    m_bDebug = false;
    
    m_qslExcept = (QStringList()
	   << "."
	   << ".."
	   << "Common Files"
	   << "Microsoft Analysis Services"   /*???*/
	   << "MSBuild"
	   << "Windows NT"
	   << "WindowsUpdate"
   );
	
	
    m_qslDirs = (QStringList()
		<< "AVAST Software"
		<< "Oracle"
		<< "Games"
		<< "ubisoft"
		<< "Microsoft Office"
	);

	m_mapProgInfo["Microsoft Office"] = "Microsoft Office";
	m_mapProgInfo["ubisoft"] = "unknown";
	m_mapProgInfo["AVAST Software"] = "Antivirus";
	m_mapProgInfo["Embarcadero"] = "http://www.embarcadero.com/";
	
}

taskSearchProgrammWin::~taskSearchProgrammWin(){}

// --------------------------------------------------------------------

QString taskSearchProgrammWin::manual()
{
	return "\t--debug - viewing debug messages";
}

// --------------------------------------------------------------------

void taskSearchProgrammWin::setOption(QStringList options)
{
    if (options.contains("--debug"))
            m_bDebug = true;
}

// --------------------------------------------------------------------

QString taskSearchProgrammWin::command()
{
	return "programs";
}

// --------------------------------------------------------------------

bool taskSearchProgrammWin::supportOS(const coex::typeOS &os)
{
	return ((os == coex::ceWindowsXP) || (os == coex::ceWindows7));
}

// --------------------------------------------------------------------

QString taskSearchProgrammWin::name()
{
	return m_strName;
}

// --------------------------------------------------------------------

QString taskSearchProgrammWin::description()
{
	return m_strDescription;
}

// --------------------------------------------------------------------

bool taskSearchProgrammWin::test()
{
	// unit test
	return true;
};

// --------------------------------------------------------------------

/*
QStringList taskSearchProgrammWin::getSubDirs(QString dirStr)
{
    QStringList dirList;
    QDirIterator dirit(dirStr, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(dirit.hasNext())
    {
        QString str = QString("%1").arg(dirit.next());
        QStringList buf = str.split(dirStr, QString::SkipEmptyParts);
        buf = buf.at(0).split("/", QString::SkipEmptyParts);
        if (buf[0].split(".").size() != 1) continue;  // посмореть такие фильтры при которых будут выводиться только субдирриктории
        if (taskSearchProgrammWin::m_qslExcept.contains(buf[0])) continue;
        if (!dirList.contains(buf[0]))
        {
            dirList << buf[0];
        }
    }
    return dirList;
};
*/
// --------------------------------------------------------------------

void taskSearchProgrammWin::recourceDirs(
	QString baseFolder, 
	QString parentFolder, 
	QString dirStr, 
	QXmlStreamWriter* xmlWrite, 
	int &idFolder, 
	int depth, 
	int maxdepth
)
{
	if(depth >= maxdepth)
		return;
	
    QStringList dirList;
    QDir dir(baseFolder + "/" + dirStr);
    
    xmlWrite->writeStartElement("folder");
    xmlWrite->writeAttribute("id", QString::number(idFolder++,10));
    xmlWrite->writeAttribute("name", dirStr);
    
    {
		xmlWrite->writeStartElement("info");
		{
			xmlWrite->writeStartElement("param");
			xmlWrite->writeAttribute("name", "parentFolder");
			xmlWrite->writeAttribute("value", parentFolder);
			xmlWrite->writeEndElement();
			
			xmlWrite->writeStartElement("param");
			xmlWrite->writeAttribute("name", "depth");
			xmlWrite->writeAttribute("value", QString::number(depth,10));
			xmlWrite->writeEndElement();
			
			if(m_mapProgInfo.contains(dirStr))
			{
				xmlWrite->writeStartElement("param");
				xmlWrite->writeAttribute("name", "description");
				xmlWrite->writeAttribute("value", m_mapProgInfo[dirStr]);
				xmlWrite->writeEndElement();
			}
		}
		xmlWrite->writeEndElement();
	}
	xmlWrite->writeEndElement();

    QStringList list = dir.entryList(QDir::AllDirs | QDir::NoSymLinks);
    for(int i = 0; i < list.size(); i++)
    {
		QString str = list.at(i);
		if(str != "." && str != "..")
		{
			recourceDirs(baseFolder + "/" + dirStr, parentFolder + "/" + dirStr, str, xmlWrite, idFolder, depth + 1, maxdepth);
		}
	}
	
	
};

// --------------------------------------------------------------------

bool taskSearchProgrammWin::execute(const coex::config &config)
{   
    {
        QDir dir(config.outputFolder);
        dir.mkdir("programs");
    }
    
    QStringList listOfDirsForProgramFiles;

    listOfDirsForProgramFiles << "Program Files";
    listOfDirsForProgramFiles << "Program Files (x86)";
    listOfDirsForProgramFiles << "Program Files(x86)";
    
    QFile fileXML(config.outputFolder + "/programs/programs.xml");
	if(!fileXML.open(QFile::WriteOnly))
	{
		std::cout << "File not found" << std::endl;
		return false;
	}
    
	QXmlStreamWriter* xmlWrite = new QXmlStreamWriter();
	xmlWrite->setDevice(&fileXML);
	xmlWrite->setAutoFormatting(true);
	xmlWrite->writeStartDocument();
	xmlWrite->writeStartElement("programfiles");
	int idFolder = 0;
	for (int i = 0; i < listOfDirsForProgramFiles.size(); i++)
	{
		recourceDirs( config.inputFolder, "", listOfDirsForProgramFiles[i], xmlWrite, idFolder);
	}
	
	xmlWrite->writeEndElement();
	xmlWrite->writeEndDocument();
	delete xmlWrite;	
	return true;
}
		
