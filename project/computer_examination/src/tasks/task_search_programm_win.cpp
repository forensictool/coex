#include "task_search_programm_win.h"
#include <iostream>
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
}
bool taskSearchProgrammWin::execute(const coex::config &config)
{ 
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    {
        QDir dir(config.outputFolder);
        dir.mkdir("programs");
    }
    QStringList *programFiles = new QStringList();
    switch (config.os)
    {
        case coex::ceWindowsXP:
        {
            QString dirStr(config.inputFolder);
            dirStr += "/Program Files/";
            *programFiles = getSubDirs(dirStr);

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
            xmlWrite->writeStartElement("programs");

            for (int i = 0; i < programFiles->size(); i++)
            {
                //fout << programFiles->at(i) << '\n';
                //std::cout << programFiles->at(i).toStdString() << std::endl;
                /*QStringList qsl = getSubDirs(dirStr + programFiles->at(i) + "/");
                for (int j = 0; j < qsl.size(); j++)
                    std::cout << qsl.at(j).toStdString() << std::endl;
                std::cout << std::endl;*/
                if(!taskSearchProgrammWin::m_qslDirs.contains(programFiles->at(i)))
                {
                    xmlWrite->writeStartElement("foundProgram");
                    xmlWrite->writeAttribute("name", programFiles->at(i));
                    xmlWrite->writeEndElement();
                }
                else
                {
                    xmlWrite->writeStartElement("dir");
                    QString dirStr(config.inputFolder);
                    dirStr += ("/Program Files/" + programFiles->at(i));
                    QStringList bufList = getSubDirs(dirStr);
                    xmlWrite->writeAttribute("name", programFiles->at(i));
                    for (int j = 0; j < bufList.size(); j++)
                    {
                        xmlWrite->writeStartElement("foundProgram");
                        xmlWrite->writeAttribute("name", bufList.at(j));
                        xmlWrite->writeEndElement();
                    }
                    xmlWrite->writeEndElement();
                }
            }


            xmlWrite->writeEndElement();
            xmlWrite->writeEndDocument();
            delete xmlWrite;
            //file.flush();
            //file.close();
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
		
