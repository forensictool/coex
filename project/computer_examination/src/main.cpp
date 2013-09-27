#include <stdio.h>
#include <iostream>
#include <QString>
#include <QVector>
#include "coex/coex.h"

// ------------------------------------------------------------------

int main( int argc, const char* argv[] )
{
	if(argc < 3)
	{
		std::cout << "\nusage: " << argv[0] << " [OPTIONS] <input folder> <output folder>\n\n";
		return -1;
	};
	
  // fill config
	coex::config cnf;
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
	for(int i = 0; i < tasks.size(); i++)
	{
		std::cout << "Task: " << tasks[i]->name().toStdString() << "\n";
		std::cout << "Description: " << tasks[i]->description().toStdString() << "\n";
		tasks[i]->execute(cnf);
	}
	
	return 0;
};
