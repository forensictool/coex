#include <stdio.h>
#include <iostream>
#include <QString>
#include <QVector>
#include "task.h"
#include "example_task.h"

int main( int argc, const char* argv[] )
{
	if(argc != 3)
	{
		std::cout << "\nusage: " << argv[0] << " <input folder> <output folder>\n\n";
		return -1;
	};
	
	coex::config cnf;
	cnf.inputFolder = QString(argv[1]);
	cnf.outputFolder = QString(argv[2]);
	cnf.os = coex::ceUnknown;
	
	// detection system
	cnf.os = coex::ceWindowsXP;
	
	// print config
	std::cout << "\tInput Folder: " << cnf.inputFolder.toStdString() << "\n";
	std::cout << "\tOutput Folder: " << cnf.outputFolder.toStdString() << "\n";
	std::cout << "\tType OS: " << cnf.os << "\n";
			
	
	QVector<coex::task*> tasks;
	
	// creating tasks
	coex::createTask<exampleTask>(cnf.os, tasks);
	
	
	// executing tasks
	for(int i = 0; i < tasks.size(); i++)
	{
		std::cout << "Task: " << tasks[i]->name().toStdString() << "\n";
		std::cout << "Description: " << tasks[i]->description().toStdString() << "\n";
		tasks[i]->execute(cnf);
	}
	
	return 0;
};
