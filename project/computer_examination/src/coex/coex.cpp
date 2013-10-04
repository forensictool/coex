#include "coex.h"
#include <stdio.h>
#include <iostream>
#include <QFile>
#include <QXmlStreamWriter>

namespace coex {

	QString typeOStoString(const coex::typeOS &os)
	{
		
		if(os == coex::ceUnknown)
			return "Unknown";
		else if(os == coex::ceLinux)
			return "Linux";
		else if(os == coex::ceWindows95)
			return "Windows 95";
		else if(os == coex::ceWindows98)
			return "Windows 98";
		else if(os == coex::ceWindowsXP)
			return "Windows XP";
		else if(os == coex::ceWindowsVista)
			return "Windows Vista";
		else if(os == coex::ceWindows7)
			return "Windows 7";
		else if(os == coex::ceWindows8)
			return "Windows 8";
		else 
			return QString((int)os);
	};

	void printConfig(const coex::config& cnf)
	{
		// print config
		std::cout << "  Config\n";
		std::cout << "\tInput Folder: " << cnf.inputFolder.toStdString() << "\n";
		std::cout << "\tOutput Folder: " << cnf.outputFolder.toStdString() << "\n";
		std::cout << "\tType OS: " << coex::typeOStoString(cnf.os).toStdString() << "\n";
	};

	bool writeConfig(const coex::config& cnf)
	{
		QFile file(cnf.outputFolder + "//coex_config.xml");

		// open a file
		if (file.open(QIODevice::WriteOnly))
		{	
			QXmlStreamWriter* xmlWriter = new QXmlStreamWriter();
			xmlWriter->setDevice(&file);
			xmlWriter->setAutoFormatting(true);
			xmlWriter->writeStartDocument();

			xmlWriter->writeStartElement("Config");
			
			xmlWriter->writeStartElement("InputFolder");
			xmlWriter->writeCharacters(cnf.inputFolder);
			xmlWriter->writeEndElement();

			xmlWriter->writeStartElement("OutputFolder");
			xmlWriter->writeCharacters(cnf.outputFolder);
			xmlWriter->writeEndElement();

			xmlWriter->writeStartElement("TypeOS");
			xmlWriter->writeCharacters(coex::typeOStoString(cnf.os));
			xmlWriter->writeEndElement();
			
			xmlWriter->writeEndElement();
			xmlWriter->writeEndDocument();
			delete xmlWriter;
			return true;
		};
		return false;
	};
	
	void parseArguments(int argc, const char* argv[], QStringList &list)
	{
		if(argc < 1) return;
		
		for(int i = 1; i < argc; i++)
			list << QString(argv[i]);
			
		
	};
	
	void printManual(const QString &nameProgram, QVector<coex::task*> &man_tasks)
	{
		std::cout << "\nusage: " << nameProgram.toStdString() << " [OPTIONS]|:all <input folder> <output folder>\n\n";
			
		std::cout << "Number of tasks: " << man_tasks.size() << "\n\n";
		for(int i=0; i < man_tasks.size(); i++)
		{
			std::cout << "  :" << man_tasks[i]->command().toStdString() << 
				" - task name '" << man_tasks[i]->name().toStdString() << "'\n"
				<< man_tasks[i]->manual().toStdString() << "\n\n";
		}
		
		std::cout << "\n-------------\n" 
		<< "\nexample usage: " << nameProgram.toStdString() << " :exampleTask --debug :pidgin --show /mnt/winxp /mnt/flashcard\n\n";	
	};
};
