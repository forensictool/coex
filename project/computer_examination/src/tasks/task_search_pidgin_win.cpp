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
            // open a file
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QStringList fieldsZero;
                QStringList fieldsOne;
                QString time;
                QString author;
                QString message;
                QRegExp rxTime ("([0-9][0-9]:[0-9][0-9]:[0-9][0-9])");
                QRegExp rxAuthor (":$");
                QRegExp rxMessage ("^ ");
                QTextStream in(&file);

                QString line = in.readLine();//read first line, get interesting info)
                fieldsZero = line.split(QRegExp(" |/|<|>"),QString::SkipEmptyParts);
                if(fieldsZero.size() > 19) //костыль, спасибо Димке за это))
                {
                    ololo.writeInfoLog(fieldsZero.at(10), fieldsZero.at(18), fieldsZero.at(19));
                }

                while(!in.atEnd())
                {
                    line = in.readLine(); // read all file
                    fieldsOne = line.split(QRegExp("<|/|>"),QString::SkipEmptyParts);

                    for(int y = 0; y< fieldsOne.size(); y++)
                    {
                        if (fieldsOne.size() > 1)
                        {
                            if(fieldsOne.at(y).contains(rxAuthor))
                            {
                                author = fieldsOne.at(y);
                                continue;
                            }
                            if(fieldsOne.at(y).contains(rxTime))
                            {
                                time = fieldsOne.at(y);
                                continue;
                            }
                            if(fieldsOne.at(y).contains(rxMessage))
                            {
                                message = fieldsOne.at(y);
                                continue;
                            }
                        }
                    }
                    ololo.writeMessage(author,time,message);
                }
            }
            else
            {
                std::cout << "could not opening file: " << fileInfo.absolutePath().toStdString() << "\r\n";
            }
        }
        if (fileInfo.suffix() == "txt")
        {
            QFile file(fileInfo.absoluteFilePath());
            // open a file
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                while(!file.atEnd())
                {
                    QString line = file.readLine();
                    QRegExp rx("\\((\\d{2}:\\d{2}:\\d{2})\\)[ ]*(.*):(.*)$");
                    //rx.setCaseSensitive( false );
                    rx.indexIn(line);
                    QString time = rx.cap(1);
                    QString author = rx.cap(2);
                    QString message = rx.cap(3);
                    //std::cout <<"\n::time:: "<< time.toStdString() <<"\n ::author:: "<< author.toStdString() <<"\n ::message:: "<< message.toStdString() << std::endl;
                    ololo.writeMessage(author,time,message);
                }
            }

            else
            {
                std::cout << "could not opening file: " << fileInfo.absolutePath().toStdString() << "\r\n";
            }
        }
    }
    std::cout << "===========================================\n\n";
    return true;
};
