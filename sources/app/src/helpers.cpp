#include "helpers.h"

#include <QDirIterator>
#include <QLibrary>

bool checkArgs(int argc, char* argv[]) {
	if (argc < 3)
		return false;
	return true;
};

void printHelp(int argc, char* argv[]) {
	QString nameProgram(argv[0]);
	std::cout << "\nUsage " << nameProgram.toStdString() << " <inputFolder> <outputFolder> \n";
	std::cout << "\nor Usage --listdetectos \n";
};


namespace coex
{
	void printConfig(const coex::config& cnf)
	{
		// print config
		std::cout << "\tConfig\n";
		std::cout << "\tInput Folder: " << cnf.inputFolder.toStdString() << "\n";
		std::cout << "\tOutput Folder: " << cnf.outputFolder.toStdString() << "\n";
		std::cout << "\tType OS: " << coex::typeOStoString(cnf.os).toStdString() << "\n";
	};

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

	void initLibs(const coex::config& cnf)
	{
		QDirIterator libsDir("../bin/libs/", QDir::Files | QDir::NoSymLinks);
		while(libsDir.hasNext())
		{
			QString str = QString("%1").arg(libsDir.next());
			std::cout << str.toStdString() << "\n";

			QLibrary lib(str);

			typedef QString (*Fct) ();
			Fct fct = (Fct)(lib.resolve("getLibName"));
			if(fct)
			{
				std::cout << fct().toStdString() << "\n";
			}
			else
			{
				std::cout << str.toStdString() << " is not library\n";
				continue;
			}

			typedef bool (*Exec) (const coex::config & );
			Exec exec = (Exec)(lib.resolve("execute"));
			if(exec)
			{
				exec(cnf);
			}
			else
			{
				std::cout << "execute not found =)" << std::endl;
			}
		}
	}
}
