
#include "coex.h"
#include "helpers.h"

#include <QCoreApplication>
#include <QApplication>
#include <iostream>
#include <QString>
#include <QLibrary>
#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QIODevice>
#include <QList>
#include <QStringList>
#include <QDir>
#include <QVector>


int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);
    QString nameProgram(argv[0]);
    
    if (argc < 3) {
		std::cout << " Usage " << nameProgram.toStdString() << " <inputFolder> <outputFolder> \n";
		return -1;
	};
	
    QString inputFolder = QString(argv[1]);
    QString outputFolder = QString(argv[2]);
    
	std::cout << "\nLoad plugins.\n";

	typedef coex::IDetectOperationSystem* (*funcCreateDetectOperationSystem) ();
	typedef coex::ITask* (*funcCreateTask) ();
	
	QDir dirPlugins(app.applicationDirPath() + "/plugins");
	
	QVector<coex::IDetectOperationSystem*> detectOS;
	QVector<coex::ITask*> tasks;
	QVector<QLibrary*> plugins;
	
	
	// std::cout << dirPlugins.absolutePath().toStdString() << "\n";
	// std::cout << QApplication::applicationFilePath().toStdString() << "\n";
	
	// load plugins
	{
		QStringList files;
		files = dirPlugins.entryList(QStringList("lib*.so"), QDir::Files);
		
		for (int i = 0; i < files.size(); ++i) {
			QLibrary *plugin = new QLibrary(dirPlugins.absolutePath() + "/" + files.at(i));
			std::cout << " * loading plugin '" << files.at(i).toStdString() << "'  .... ";
			
			bool bIsPlugin = false;
			
			funcCreateDetectOperationSystem createDetect = (funcCreateDetectOperationSystem)(plugin->resolve("createDetectOperationSystem"));
			if(createDetect)
			{
				bIsPlugin = true;
				coex::IDetectOperationSystem* detect = createDetect();
				std::cout << "OK \n\t'" << detect->name().toStdString() << "' by " << detect->author().toStdString();
				detectOS.push_back(detect);
			}
			
			funcCreateTask createTask = (funcCreateTask)(plugin->resolve("createTask"));
			if(createTask) {
				bIsPlugin = true;
				coex::ITask* task = createTask();
				std::cout << "OK (by " << task->author().toStdString() << ") ";
				tasks.push_back(task);
			}
			
			if (bIsPlugin) {
				plugins.push_back(plugin);
			} else {
				plugin->unload();
			}
			
			std::cout << "\n";
		}
	}
	
	// detect operation system
	coex::ITypeOperationSystem* typeOS = NULL;
	{
		// detect
		for (int i = 0; i < detectOS.size(); i++) {
			coex::ITypeOperationSystem* tmpTypeOS = detectOS[i]->detect(inputFolder);
			if (tmpTypeOS != NULL && typeOS != NULL) {
				std::cout << "ERROR: found ambiguity\n";
				return -2;
			}
			typeOS = tmpTypeOS;
		}
	}

	if (typeOS == NULL) {
		std::cout << "ERROR: could not detected Operation System\n";
		return -3;
	}

	// found and run tasks

	// 
	
   /* Fct detOS = (Fct)(lib.resolve("detectOS"));
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
    }*/
    
    return 0;
    /*
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
*/
    return 0;
}
