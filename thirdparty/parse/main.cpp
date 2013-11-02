#include <QCoreApplication>
#include <iostream>
#include <QStringList>
#include <QString>
#include <QDirIterator>


int mode_loglist = 0;
int mode_meta = 0;
int print_verbose = 0;
int print_header = 1;
QString DB_PATH;
QString LOG;


int main(int argc, char *argv[])
{
    if((argc < 3) | !(strcmp(argv[1], "-?")) | !(strcmp(argv[1], "--help")))
    {
        std::cout << "NO_1" << std::endl;
        return false;
    }
    else if (!strcmp(argv[1], "-l"))
    {
        if (argc == 3)
        {
            mode_loglist = 1;
            DB_PATH = argv[2];
        }
        else
        {
            std::cout << "ERROR: Incorrect usage for log list mode" << std::endl;
            return false;
        }
    }
    else if (!strcmp(argv[1], "-m"))
    {
        if (argc == 4)
        {
            mode_meta = 1;
            DB_PATH = argv[2];
            LOG = argv[3];
        }
        else
        {
            std::cout << "ERROR: Incorrect usage for meta information mode" << std::endl;
            return false;
        }
    }
    else if (argc >= 3)
    {
        DB_PATH = argv[argc - 2];
        LOG = argv[argc - 1];

        for(int i = 0; i < argc - 2; i++)
        {
            if (!strcmp(argv[i], "-v"))
            {
                print_verbose = 1;
            }
            else if (!strcmp(argv[i], "-H"))
            {
                print_header = 0;
            }
            else if (!strcmp(argv[i], "-h"))
            {
                print_header = 1;
            }
            else
            {
                std::cout << "ERROR: Unrecognized option " << argv[i] << std::endl;
                return false;
            }
        }
    }
    else
    {
        std::cout << "ERROR: Incorrect usage for log parse command" << std::endl;
        return false;
    }

    if (mode_loglist)
    {
        QDirIterator dirIt(DB_PATH+"/services", QDir::NoSymLinks | QDir::Files, QDirIterator::Subdirectories);
        while (dirIt.hasNext())
        {
            std::cout << dirIt.next().toStdString() << std::endl;
        }
        if (print_verbose)
        {
            std::cout << "INFO: Opening message repository " << DB_PATH.toStdString() << std::endl;
            //строка 161.
        }
    }


    return true;
}
