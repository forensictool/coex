#include "task_search_pidgin_win.h"
#include "../coex/writerMessages.h"
#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include<QTextStream>

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
	if(m_bDebug)
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

    QString time;
    QString author;
    QString message;
    QString chatID;
    QString account;
    QString data;
    QString protocol;

    for(int i = 0; i < foundFile.size(); ++i)
    {
        QFileInfo fileInfo = foundFile.at(i);
        if (fileInfo.suffix() == "html")
        {
            QFile file(fileInfo.absoluteFilePath());
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QRegExp rxHead(".*h3.*with (.*) at (.*) on (.*)\\/ \\((.*)\\)");
                QTextStream in(&file);
                QString line = file.readLine();//read first line, get interesting info)
                rxHead.indexIn(line);
                chatID = rxHead.cap(1);
                account = rxHead.cap(2);
                data = rxHead.cap(3);
                protocol = rxHead.cap(4);
                if(m_bDebug)
                    std::cout <<"\n::1:: "<< chatID.toStdString() <<"\n ::2:: "<< account.toStdString() <<"\n ::3:: "<< data.toStdString() <<"\n ::4:: " << protocol.toStdString() <<"\n";
                ololo.writeInfoLog(chatID, data, account, protocol);
                QRegExp rxBody(".*(\\d{2}:\\d{2}:\\d{2}).*b\\>(.*):\\<\\/b.*font\\>(.*)\\<br");
                while(!in.atEnd())
                {
                    line = in.readLine(); // read all file
                    rxBody.indexIn(line);
                    time = rxBody.cap(1);
                    author = rxBody.cap(2);
                    message = rxBody.cap(3);
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
                QRegExp rxHead(".*with (.*) at (.*) on (.*)\\/ \\((.*)\\)");
                QString line = file.readLine();//read first line, get interesting info)
                rxHead.indexIn(line);
                chatID = rxHead.cap(1);
                account = rxHead.cap(2);
                data = rxHead.cap(3);
                protocol = rxHead.cap(4);
                if(m_bDebug)
                    std::cout <<"\n::1:: "<< chatID.toStdString() <<"\n ::2:: "<< account.toStdString() <<"\n ::3:: "<< data.toStdString() <<"\n ::4:: " << protocol.toStdString() <<"\n";
                ololo.writeInfoLog(chatID, data, account, protocol);
                QRegExp rxBody("\\((\\d{2}:\\d{2}:\\d{2})\\)[ ]*(.*):(.*)$");
                while(!file.atEnd())
                {
                    line = file.readLine();
                    rxBody.indexIn(line);
                    time = rxBody.cap(1);
                    author = rxBody.cap(2);
                    message = rxBody.cap(3);
                    ololo.writeMessage(author,time,message);
                }
            }
            else
            {
                std::cout << "could not opening file: " << fileInfo.absolutePath().toStdString() << "\r\n";
            }
        }
    }
    if(m_bDebug)
      std::cout << "===========================================\n\n";
    return true;
};
