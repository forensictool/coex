#include <stdio.h>
#include <iostream>
#include <QString>
#include <QVector>
#include <QDir>
#include "coex/coex.h"

// ------------------------------------------------------------------

int main( int argc, const char* argv[] )
{
	QString nameProgram(argv[0]);
	coex::config cnf;
	bool bExecAllTasks = false;
	QStringList listArgs;
	// parse and show help
	{
		// init tasks	
		QVector<coex::task*> man_tasks;
		coex::initTasks(cnf.os, man_tasks, true);
		
		coex::parseArguments(argc, argv, listArgs);
		if(listArgs.count() < 3)
		{
			// std::cout << "\nusage: " << nameprogram.toStdString() << " [OPTIONS] <input folder> <output folder>\n\n";
			printManual(nameProgram, man_tasks);
			return -1;
		}
		else
		{
			if(listArgs.contains("--help") || listArgs.contains("/?") || listArgs.contains("?"))
			{
				printManual(nameProgram, man_tasks);
				return -2;
			}
			
			cnf.inputFolder = listArgs[listArgs.count()-2];
			cnf.outputFolder = listArgs[listArgs.count()-1];
			QDir inputDir(cnf.inputFolder);
			if(!inputDir.exists())
			{
				std::cout << "\nfolder '" << cnf.inputFolder.toStdString() << "' is not exists\n\n";
				return -3;
			};

			bExecAllTasks = (listArgs[0] == ":all");
			// coex::printConfig(cnf);
		};
	}
	
	// fill config
	
	cnf.inputFolder = QString(argv[argc-2]);
	cnf.outputFolder = QString(argv[argc-1]);
	
	// detection system
	cnf.os = coex::detectOS(cnf.inputFolder);
	
	// print config
	coex::printConfig(cnf);

	// check results after detect os
	if(cnf.os == coex::ceUnknown)
	{
		std::cout << "\tCould not detected os!\n";
		return -1;
	};

	// write config to file
	if(!coex::writeConfig(cnf))
	{
		std::cout << "\tCould not write config to file!\n";
		return -2;
	};

	// init tasks	
	QVector<coex::task*> tasks;	
	coex::initTasks(cnf.os, tasks);
  	
	// executing tasks
	
	if(!bExecAllTasks)
	{
		printManual(nameProgram, tasks);
		return -4;
	}
	
	std::cout << "\n  Executing ALL tasks\n\n";
	for(int i = 0; i < tasks.size(); i++)
	{
		if(bExecAllTasks || listArgs.contains(":"+tasks[i]->command()))
		{
			std::cout << "\tTask: " << tasks[i]->name().toStdString() << "\n";
			std::cout << "\t\tDescription: " << tasks[i]->description().toStdString() << "\n";
			tasks[i]->execute(cnf);
			std::cout << "\n\n";
		}
	}
	
	return 0;
};
