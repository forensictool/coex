#include "coex/coex.h"

#include <iostream>
#include <QString>

int main(int argc, char* argv[])
{
    QString nameProgram(argv[0]);
    coex::config cnf;
    cnf.inputFolder = QString(argv[argc - 2]);
    cnf.outputFolder = QString(argv[argc - 1]);
    coex::printConfig(cnf);
    
    coex::initLibs();

    return 0;
}