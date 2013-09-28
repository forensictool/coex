#include "task_search_pidgin_win.h"
#include <iostream>
#include <QDir>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>

taskSearchPidginWin::taskSearchPidginWin()
{
	m_strName = "Search Pidgin (Win)";
	m_strDescription = "Task is search logs of Pidgin for WINDOWS";
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

bool taskSearchPidginWin::execute(const coex::config &config)
{
  // TODO: 

	std::cout << "===========================================\n\n";
	// std::cout << config.inputFolder.toStdString() << "\n";
	// std::cout << config.outputFolder.toStdString() << "\n";

    QString path = config.inputFolder + "/Users/Default/AppData/Roaming/.purple";

    path = path + "/logs/jabber/fox.user.3@gmail.com/ctf@conference.jabber.ru.chat"; //hard code 

    QDir dir(path);

    dir.setFilter(QDir::Files | QDir::Dirs  | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QStringList filters;
    filters << "*.html" << "*.txt";
    dir.setNameFilters(filters);

    QFileInfoList list = dir.entryInfoList();
    std::cout << " Bytes FileName " << std::endl;
    for(int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        std::cout << qPrintable(QString("%1 %2" ).arg(fileInfo.size(), 10).arg(fileInfo.fileName()));
        std::cout << std::endl;
        //QString fileName = fileInfo.fileName();
    
		//QFileInfo info(fileName);

		std::cout << "FILE " << fileInfo.suffix().toStdString() << "\n\n";

		if (fileInfo.suffix() == "html") 
		{
			std::cout << "воу воу парень, полегше. есть тут HTML\n\n";

			QFile file(fileInfo.absolutePath());

			// open a file
			if (file.open(QIODevice::ReadOnly | QIODevice::Text))
			{	
				QXmlStreamReader xml(&file);
				while(!xml.atEnd() && !xml.hasError())
				{
					QXmlStreamReader::TokenType token = xml.readNext();
					if(token == QXmlStreamReader::StartDocument) 
					{
            			continue;
        			}
        			

        			if(token == QXmlStreamReader::StartElement) 
        			{
						//if(xml.name() == "title") {
						///	continue;
						//}
					}

					if(token == QXmlStreamReader::Characters)
					{
						// if(xml.name() == "title") {
							std::cout << QString(xml.text().data()).toStdString() << ".";
						//}	
					}

					 

					if(token == QXmlStreamReader::EndElement)
					{
						if(xml.name() == "title")
						{
								std::cout << QString(xml.text().data()).toStdString() << ".";
						}
					}
				}

				if( xml.hasError())
					std::cout << xml.errorString().toStdString();
			};

		} 

		if (fileInfo.suffix() == "txt") 
		{
			std::cout << "воу воу парень, полегше. есть тут txt\n\n";

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

		return true;
	
    }
    std::cout << "===========================================\n\n";	
};
		
