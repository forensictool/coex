#include "task_search_pidgin_win.h"
#include <iostream>
#include <QDir>
#include <QDirIterator>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QRegExp>
#include <QTextStream>
#include <QDebug>

taskSearchPidginWin::taskSearchPidginWin()
{
	m_strName = "Search Pidgin (Win)";
	m_strDescription = "Task is search logs of Pidgin for WINDOWS";
	m_bDebug = false;
};

QString taskSearchPidginWin::manual()
{
	return "\t--debug - viewing debug messages";
};

void taskSearchPidginWin::setOption(QStringList options)
{
	if(options.contains("--debug"))
		m_bDebug = true;
};

QString taskSearchPidginWin::command()
{
	return "pidgin";
};

bool taskSearchPidginWin::supportOS(const coex::typeOS &os)
{
	return ((os == coex::ceWindowsXP) || (os == coex::ceWindows7));
};

QString taskSearchPidginWin::name()
{
	return m_strName;
};

QString taskSearchPidginWin::description()
{
	return m_strDescription;
};

bool taskSearchPidginWin::test()
{
	// unit test
	return true;
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

bool taskSearchPidginWin::execute(const coex::config &config)
{
	// example usage options
	if(m_bDebug)
		std::cout << "  !!! debug mode on.\n";

	{
		QDir dir(config.outputFolder);
		dir.mkdir("pidgin");
	}
	
	QFile fileXML(config.outputFolder + "//pidgin/messages.xml");
	// open a file
	if (!fileXML.open(QIODevice::WriteOnly))
	{
		std::cout << " failed task\n";
		return false;
	}
	QXmlStreamWriter* xmlWriter = new QXmlStreamWriter();

	xmlWriter->setDevice(&fileXML);
	xmlWriter->setAutoFormatting(true);
	xmlWriter->writeStartDocument();
	xmlWriter->writeStartElement("Messages");
			
  // TODO: 
	
	std::cout << "===========================================\n\n";
	// std::cout << config.inputFolder.toStdString() << "\n";
	// std::cout << config.outputFolder.toStdString() << "\n";

    QString path = config.inputFolder + "/Users/Default/AppData/Roaming/.purple";

    path = path + "/logs"; //hard code ... or not

    QStringList foundFile;
    QDirIterator dirPath (path, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(dirPath.hasNext())
    {

        QFileInfo fileInfo = dirPath.next();
        //std :: cout << fileInfo.absoluteFilePath().toStdString() << std::endl;
        if (fileInfo.suffix() == "html" || fileInfo.suffix() == "txt")
        {
            //std :: cout << fileInfo.baseName().toStdString() << std::endl;
            foundFile << fileInfo.absoluteFilePath();
        }
    }

    for(int i = 0; i < foundFile.size(); ++i)
    {
        QFileInfo fileInfo = foundFile.at(i);
        xmlWriter->writeStartElement("FoundFile");
		xmlWriter->writeAttribute("size", QString::number(fileInfo.size()));
		xmlWriter->writeAttribute("suffix", fileInfo.suffix());
		xmlWriter->writeAttribute("name", fileInfo.fileName());

		if (fileInfo.suffix() == "html") 
		{
			QFile file(fileInfo.absoluteFilePath());
			// open a file
			if (file.open(QIODevice::ReadOnly))
			{	
                QTextStream in(&file);
                QStringList fieldsOne;
                QStringList fieldsTwo;
                QStringList fieldsEnd;
                while(!in.atEnd())
                {
                    QString line = in.readLine();
                    fieldsOne = line.split("<",QString::SkipEmptyParts);
                    for (int y = 0; y < fieldsOne.size(); y++)
                    {
                        fieldsTwo = fieldsOne.at(y).split(">", QString::SkipEmptyParts);
                        if (fieldsTwo.size() > 1)
                        {
                            fieldsEnd += fieldsTwo[1];
                        }
                    }
                }
				QXmlStreamReader xml(&file);
                while(!xml.atEnd() && !xml.hasError())
				{
					QXmlStreamReader::TokenType token = xml.readNext();
					if(token == QXmlStreamReader::StartDocument) 
					{
            			continue;
        			}

                    QRegExp rxTime ("([0-9][0-9]:[0-9][0-9]:[0-9][0-9])");
                    QRegExp rxAuthor (":$");

                    for (int l = 0; l < fieldsEnd.size(); l++)
                    {
                        if(fieldsEnd.at(l).contains("conversation", Qt::CaseInsensitive) )
                        {
                            xmlWriter->writeStartElement("info");
                            xmlWriter->writeCharacters(fieldsEnd.at(l));
                            xmlWriter->writeEndElement();
                            continue;
                        }
                        if(fieldsEnd.at(l).contains(rxTime))
                        {
                            xmlWriter->writeStartElement("time");

                            QString formatTime = fieldsEnd.at(l).mid(1, 8);

                            xmlWriter->writeCharacters(formatTime);
                            xmlWriter->writeEndElement();

                            /*xmlWriter->writeStartElement("message");
                            //xmlWriter->writeCharacters(fieldsEnd.at(l));
                            a = l;
                            xmlWriter->writeAttribute("time", fieldsEnd.at(a));
                            //a++;
                            xmlWriter->writeAttribute("author", fieldsEnd.at(a));
                            //a++;
                            xmlWriter->writeAttribute("text", fieldsEnd.at(a));
                            xmlWriter->writeEndElement();*/

                            continue;
                        }
                        if(fieldsEnd.at(l).contains(rxAuthor))
                        {
                            xmlWriter->writeStartElement("author");
                            //QString y = fieldsEnd.at(l).mid(0, size.(fieldsEnd.at(l)));
                            //xmlWriter->writeCharacters(fieldsEnd.at(l));
                            xmlWriter->writeAttribute("AUTHOR", fieldsEnd.at(l));
                            xmlWriter->writeEndElement();
                            continue;
                        }
                        if( 1 )
                        {
                            xmlWriter->writeStartElement("text");
                            //xmlWriter->writeCharacters(fieldsEnd.at(l));
                            xmlWriter->writeAttribute("TEXT", fieldsEnd.at(l));
                            xmlWriter->writeEndElement();
                            continue;
                        }
                    }
                };

				if( xml.hasError())
					std::cout << xml.errorString().toStdString();
			}
			else
			{
				std::cout << "could not opening file: " << fileInfo.absolutePath().toStdString() << "\r\n";
			};

		} 

		if (fileInfo.suffix() == "txt") 
		{

			QFile file(fileInfo.absolutePath());

			// open a file
			if (file.open(QIODevice::ReadOnly))
			{	
				// QXmlStreamReader* xmlReader = new QXmlStreamReader();
				// xmlReader->setDevice(&file);
				// xmlReader->setAutoFormatting(true);
				// xmlReader->writeStartDocument();

				// delete xmlReader;
			};

		}
		// end foundfile
		xmlWriter->writeEndElement();	
    }
        
    xmlWriter->writeEndElement();
	xmlWriter->writeEndDocument();
	delete xmlWriter;
    std::cout << "===========================================\n\n";	
    return true;
};
		
