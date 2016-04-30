
#include "coex.h"
#include "helpers.h"
#include "config.h"
#include "hdd.h"

#include <unistd.h>
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

#include <QThread>

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);
  coex::IConfig *config = createConfig();
  if(!config->getArgumentsValues(argc, argv, "i:o:d"))
    {
      printHelp(argc,argv);
      return(-1);
    }

   /*if (!checkArgs(argc, argv))
      {
		printHelp(argc, argv);
		return -1;
	};


	
	
	config->setInputFolder(QString(argv[1]));
	config->setOutputFolder(QString(argv[2]));*/
    
        std::cout << "\n > Loading plugins...\n";

	typedef coex::IDetectOperationSystem* (*funcCreateDetectOperationSystem) ();
	typedef coex::ITask* (*funcCreateTask) ();
    typedef coex::IThreadTask* (*funcCreateThreadTask) ();
	
	QDir dirPlugins(app.applicationDirPath() + "/plugins");
	
	QVector<coex::IDetectOperationSystem*> detectOS;
	QVector<coex::ITask*> tasks;
    QVector<coex::IThreadTask*> threads;
	QVector<QLibrary*> plugins;
	
	
	// std::cout << dirPlugins.absolutePath().toStdString() << "\n";
	// std::cout << QApplication::applicationFilePath().toStdString() << "\n";
	
	// load plugins
	{
		QStringList files;
		files = dirPlugins.entryList(QStringList("lib*.so"), QDir::Files);
		
		for (int i = 0; i < files.size(); ++i) {
			QLibrary *plugin = new QLibrary(dirPlugins.absolutePath() + "/" + files.at(i));
            std::cout << " --> Plugin '" << files.at(i).toStdString() << "'  . . . ";
			
			bool bIsPlugin = false;
			
			funcCreateDetectOperationSystem createDetect = (funcCreateDetectOperationSystem)(plugin->resolve("createDetectOperationSystem"));
			if(createDetect)
			{
				bIsPlugin = true;
				coex::IDetectOperationSystem* detect = createDetect();
                std::cout << "OK \n ----> Found detector '" << detect->name().toStdString() << "' by '" << detect->author().toStdString() << "' ";
				detectOS.push_back(detect);
			}
			
			funcCreateTask createTask = (funcCreateTask)(plugin->resolve("createTask"));
			if(createTask) {
				bIsPlugin = true;
				coex::ITask* task = createTask();
                std::cout << "OK \n ----> Found task '" << task->name().toStdString() << "' by '" << task->author().toStdString() << "' ";
				tasks.push_back(task);
			}
			
            funcCreateThreadTask createThreadTask = (funcCreateThreadTask)(plugin->resolve("createThreadTask"));
            if(createThreadTask)
            {
                bIsPlugin = true;
                coex::IThreadTask* thread = createThreadTask();
                std::cout << "OK \n ----> Found threadTask '" << thread->name().toStdString() << "' by '" << thread->author().toStdString() << "' ";
                threads.push_back(thread);
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
    std::cout << " > Plugins loaded\n";
	
	// detect operation system
    std::cout << " > Detectiong operation system . . . \n";
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
    std::cout << " --> Detected OS: '" << config->typeOS()->toString().toStdString() << "'\n";

    // scan hdd
    std::cout << " > Running hdd parser\n";
    Hdd parsedHdd(config->inputFolder());
    //config->parsedHdd = new Hdd(config->inputFolder());

    std::cout << "Parsing is done\n";

    // run threads
    foreach (coex::IThreadTask* thread, threads)
    {
        if(thread->isSupportOS(config->typeOS()))
        {
            std::cout << " --> Run thread: '" << thread->name().toStdString() << "' by '" << thread->author().toStdString() << "'\n";
            std::cout << " ----> Init . . .";
            thread->init(config);
            std::cout << "OK\n";
            QThread* t = new QThread();
            std::cout << " ----> Running . . .";
            QObject::connect(t, SIGNAL(started()), thread, SLOT(execute()));
            QObject::connect(t, SIGNAL(finished()), thread, SLOT(deleteLater()));
            thread->moveToThread(t);
            t->start();
            std::cout << "OK\n";
        }
    }

	// found and run tasks
    if(tasks.size())
    {
        std::cout << " > Executing tasks . . .\n";
        {
            for (int i = 0; i < tasks.size(); i++) {

                if (tasks[i]->isSupportOS(config->typeOS())) {
                    std::cout << " --> Execute task: '" << tasks[i]->name().toStdString() << "' by '" << tasks[i]->author().toStdString() << "' \n";
                    tasks[i]->execute(config);
                }
            }
        }
    }
    //std::cout << " > Job done. Press Ctrl+C for exit\n";
    return 0;//app.exec();
}
