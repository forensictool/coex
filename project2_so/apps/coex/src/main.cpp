#include "coex/coex.h"

#include <iostream>
#include <QString>
#include <QLibrary>
#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QIODevice>
#include <QList>

int main(int argc, char* argv[])
{
    QString nameProgram(argv[0]);
    coex::config cnf;
    cnf.inputFolder = QString(argv[argc - 2]);
    cnf.outputFolder = QString(argv[argc - 1]);
    coex::printConfig(cnf);

    QLibrary lib("../bin/libs/libdetectOS.so.1.0.0");
    typedef QString (*Fct2)();
    Fct2 fct = (Fct2)(lib.resolve("getLibName"));
    if(fct)
    {
    	std::cout << fct().toStdString() << "\n";
	}
	else
	{
		std::cout << " is not library\n";
	}


    typedef coex::typeOS (*Fct) (QString);
    Fct detOS = (Fct)(lib.resolve("detectOS"));
    if(detOS)
    {
        std::cout << "-------------------------------------------------------------------------\n";
    	cnf.os = detOS(cnf.inputFolder);
        std::cout << "-------------------------------------------------------------------------\n";
    }
    else
    {
    	std::cout << "library is not loaded\n";
    	return (-1);
    }

    coex::printConfig(cnf);
    lib.unload();

    coex::initLibs(cnf);

    return 0;
}