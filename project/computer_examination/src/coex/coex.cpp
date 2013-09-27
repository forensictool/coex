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
};
