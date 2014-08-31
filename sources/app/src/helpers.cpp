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
	std::cout << "\nor Usage --listtaskos \n";
};
