#ifndef __HELPERS_H__
#define __HELPERS_H__

#include "coex.h"
#include <QString>
#include <iostream>

void printHelp(int argc, char* argv[]);
bool checkArgs(int argc, char* argv[]);

namespace coex
{
	void printConfig(const coex::config & cnf);
	QString typeOStoString(const coex::typeOS &os);
	void initLibs(const coex::config & cnf);
}

#endif //__HELPERS_H__
