#include "task_search_pidgin_win.h"
#include "../coex/writerMessages.h"
#include <iostream>
#include <QDir>
#include <QDirIterator>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QRegExp>
#include <QTextStream>
#include <QDebug>

taskSearchPidginWin::taskSearchPidginWin()
{
	m_strName = "Search Pidgin (Win)";
	m_strDescription = "Task is search logs of Pidgin for WINDOWS";
	m_bDebug = false;
};

QString taskSearchPidginWin::manual()
{
	return "\t--debug - viewing debug messages";
};

void taskSearchPidginWin::setOption(QStringList options)
{
	if(options.contains("--debug"))
		m_bDebug = true;
};

QString taskSearchPidginWin::command()
{
	return "pidgin";
};

bool taskSearchPidginWin::supportOS(const coex::typeOS &os)
{
	return ((os == coex::ceWindowsXP) || (os == coex::ceWindows7));
};

QString taskSearchPidginWin::name()
{
	return m_strName;
};

QString taskSearchPidginWin::description()
{
	return m_strDescription;
};

bool taskSearchPidginWin::test()
{
	// unit test
	return true;
};

bool taskSearchPidginWin::execute(const coex::config &config)
{
	// example usage options
	if(m_bDebug)
		std::cout << "  !!! debug mode on.\n";
	{
		QDir dir(config.outputFolder);
		dir.mkdir("pidgin");
	}
   /* coex::writerMessages msg(config.outputFolder + "//pidgin/messages.xml","pidgin");
    if(!msg.opened())
    {
        std::cout << " failed task\n";
        return false;
    }*/
    std::cout << "===========================================\n\n";

    QString path = config.inputFolder + "/Users/";

    QDir dir(path);
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    QFileInfoList users = dir.entryInfoList();
    QStringList foundFile;

    for( int i = 0; i < users.size();++i)
    {
        QFileInfo fileInfo = users.at(i);
        path = fileInfo.absoluteFilePath() + "/AppData/Roaming/.purple/logs";

        QDirIterator dirPath (path, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
        while(dirPath.hasNext())
        {
            QFileInfo fileInfo = dirPath.next();
            if (fileInfo.suffix() == "html" || fileInfo.suffix() == "txt")
            {
                foundFile << fileInfo.absoluteFilePath();
            }
        }
     }
    coex::writerMessages ololo(config.outputFolder + "//pidgin/messages.xml", "pidgin");
    if(!ololo.opened())
    {
        std::cout << " failed task\n";
        return false;
    }

    for(int i = 0; i < foundFile.size(); ++i)
    {
        QFileInfo fileInfo = foundFile.at(i);
		if (fileInfo.suffix() == "html") 
		{
            QFile file(fileInfo.absoluteFilePath());
            std::cout << fileInfo.absoluteFilePath().toStdString() << std::endl; //
			// open a file
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
			{	
                QStringList fieldsZero;
                QStringList fieldsOne;
                QStringList fieldsTwo;
                QString time;
                QString author;
                QString message;
                QString account;
                QString protocol;
                QString chatID;
                QRegExp rxTime ("([0-9][0-9]:[0-9][0-9]:[0-9][0-9])");
                QRegExp rxAuthor (":$");
                QRegExp rxMessage ("^ ");
                QTextStream in(&file);

                QString line = in.readLine();//read first line, get interesting info)
                fieldsZero = line.split(QRegExp(" |/|<|>"),QString::SkipEmptyParts);
                /*for (int y = 0; y < fieldsZero.size(); y++)
                        std::cout << y << "::fieldsZero :: " << fieldsZero.at(y).toStdString() <<std::endl;*/
                if(fieldsZero.size() > 19)
                {
                    chatID = fieldsZero.at(10);
                    account = fieldsZero.at(18);
                    protocol = fieldsZero.at(19);
                    ololo.writeInfoLog(chatID, account, protocol);
                }

                while(!in.atEnd())
                {
                    line = in.readLine(); // read all file
                    fieldsOne = line.split("<",QString::SkipEmptyParts);
                    for (int y = 0; y < fieldsOne.size(); y++)
                    {
                        fieldsTwo += fieldsOne.at(y).split(">", QString::SkipEmptyParts);
                    }
/*for (int y = 0; y < fieldsOne.size(); y++)
        std::cout << "\nfieldsOne :: " << fieldsOne.at(y).toStdString() <<std::endl;
for (int y = 0; y < fieldsTwo.size(); y++)
        std::cout << "\nfieldsTwo :: " << fieldsTwo.at(y).toStdString() <<std::endl;*/

                    for(int y = 0; y< fieldsTwo.size(); y++)
                    {
                        if (fieldsTwo.size() > 1)
                        {
                            if(fieldsTwo.at(y).contains(rxTime))
                            {
                                time = fieldsTwo.at(y);
                                continue;
                            }
                            if(fieldsTwo.at(y).contains(rxAuthor))
                            {
                                author = fieldsTwo.at(y);
                                continue;
                            }
                            if(fieldsTwo.at(y).contains(rxMessage))
                            {
                                message = fieldsTwo.at(y);
                                continue;
                            }
                        }
                    }
                    ololo.writeMessage(author, time, message);
                }
            //ololo.~writerMessages();  я маленько не понял, нужно деструктор или нет? думаю что нет...
			}
			else
			{
				std::cout << "could not opening file: " << fileInfo.absolutePath().toStdString() << "\r\n";
			};
		} 

		if (fileInfo.suffix() == "txt") 
		{
/*
			QFile file(fileInfo.absolutePath());
			if (file.open(QIODevice::ReadOnly))
			{	
				// QXmlStreamReader* xmlReader = new QXmlStreamReader();
				// xmlReader->setDevice(&file);
				// xmlReader->setAutoFormatting(true);
				// xmlReader->writeStartDocument();
				// delete xmlReader;
            };
*/
		}

    }
    std::cout << "===========================================\n\n";
    return true;
};
		
