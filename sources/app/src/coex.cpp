
#include "coex.h"
#include "helpers.h"
#include "config.h"

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

    if (!checkArgs(argc, argv)) {
		printHelp(argc, argv);
		return -1;
	};
	
	coex::IConfig *config = createConfig();
	
	config->setInputFolder(QString(argv[1]));
	config->setOutputFolder(QString(argv[2]));
    
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
				std::cout << "OK \n\t detector '" << detect->name().toStdString() << "' by " << detect->author().toStdString();
				detectOS.push_back(detect);
			}
			
			funcCreateTask createTask = (funcCreateTask)(plugin->resolve("createTask"));
			if(createTask) {
				bIsPlugin = true;
				coex::ITask* task = createTask();
				std::cout << "OK \n\t task '" << task->name().toStdString() << "' by " << task->author().toStdString() << " ";
				tasks.push_back(task);
			}
			
			if (bIsPlugin) {
				plugins.push_back(plugin);
			} else {
				std::cout << "NOTHING";
				plugin->unload();
			}
			
			std::cout << "\n";
		}
	}
	
	// detect operation system
	{
		coex::ITypeOperationSystem* typeOS = NULL;
		for (int i = 0; i < detectOS.size(); i++) {
			coex::ITypeOperationSystem* tmpTypeOS = detectOS[i]->detect(config->inputFolder());
			if (tmpTypeOS != NULL && typeOS != NULL) {
				std::cout << "ERROR: found ambiguity\n";
				return -2;
			}
			typeOS = tmpTypeOS;
		}
		config->setTypeOS(typeOS);
	}

	if (config->typeOS() == NULL) {
		std::cout << "ERROR: could not detected Operation System\n";
		return -3;
	}
	

	std::cout << " * Detected OS: '" << config->typeOS()->toString().toStdString() << "'\n";


	// found and run tasks
	{
		for (int i = 0; i < tasks.size(); i++) {
			
			if (tasks[i]->isSupportOS(config->typeOS())) {
				tasks[i]->execute(config);
			}
		}
	}
    
    return 0;
}
