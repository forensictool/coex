#include <QCoreApplication>
#include <iostream>
#include <QStringList>
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QDirIterator>


int mode_loglist = 0;
int mode_meta = 0;
int print_verbose = 0;
int print_header = 1;
QString DB_PATH;
QString LOG;

#define returnna return 0;

int main(int argc, char *argv[])
{
/*	if(argc < 2)
	{
		std::cout << argv[0] << " <log filename>" << std::endl;
        return -1;
	};
	
	
	QString filename = QString(argv[1]);
*/
	QString filename = QString("system.LOG");
	QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return -2;

    QDataStream stream(&file);

	for(int i=0; i < 3; i++)
	{
		QChar h;
		stream >> h;
		std::cout << h.toChar();	
	}
	
	
	qint32 val;
	stream >> val;
    std::cout << val;

    file.close();
    
    std::cout << "\r\n fuck off \r\n";
    return 0;
	// DWORD f;
	
    /*if((argc < 3) | !(strcmp(argv[1], "-?")) | !(strcmp(argv[1], "--help")))
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
	
	*/
    return true;
}
