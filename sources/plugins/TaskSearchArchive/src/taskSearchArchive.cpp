#include "taskSearchArchive.h"

#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QFileInfo>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QDir>
#include <qtextcodec.h>

TaskSearchArchive::TaskSearchArchive() {
    m_bDebug = false;
};

QString TaskSearchArchive::help() {
	return "\t--debug - viewing debug messages";
};

QString TaskSearchArchive::name() {
	return "search Archive";
};

QString TaskSearchArchive::author() {
	return "Igor Polyakov";
};

QString TaskSearchArchive::description() {
	return "task Search Archive";
};

bool TaskSearchArchive::isSupportOS(const coex::ITypeOperationSystem *os) {
	return (os->platform() == "Windows");
};

void TaskSearchArchive::setOption(QStringList options) {
	/*
	 * 
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};

bool TaskSearchArchive::execute(const coex::IConfig *config) {
	if(m_bDebug) {
		std::cout << "  !!! debug mode on.\n";
		std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
	};

    //QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    if(m_bDebug) {
        std::cout << "---------------------------------------------------------" << std::endl;
    };
	QString dirStr(config->inputFolder());
	QString outDirStr(config->outputFolder());
    outDirStr.append("/Archives");
	QDir().mkdir(outDirStr);
    outDirStr.append("/list of found archive.txt");
	QFile outFile(outDirStr);
	if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text)&&(m_bDebug))
	{
		std::cout << "ERROR: can't open output file" << std::endl;
        return false;
	}
	QTextStream out(&outFile);
	QDirIterator fileListDirit(dirStr, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
	while(fileListDirit.hasNext())
	{
		QString str = QString("%1").arg(fileListDirit.next());
        QFileInfo fInfo(str);
        //if(m_bDebug) std::cout << fInfo.absoluteFilePath().toStdString() << std::endl;
        QFile file(fInfo.absoluteFilePath());
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString plainText = file.readLine().trimmed();

            if(plainText.contains(QRegExp("PK.*")))
            {
                if(m_bDebug) std::cout << "Find ZIP archive! on this way :: "<< fInfo.absoluteFilePath().toStdString() << std::endl;
                out << "ZIP :: " << fInfo.absoluteFilePath() << "\n";
            }
            else if(plainText.contains(QRegExp("Rar!.*")))
            {
                if(m_bDebug) std::cout << "Find RAR archive! on this way :: "<< fInfo.absoluteFilePath().toStdString() << std::endl;
                out << "RAR :: " << fInfo.absoluteFilePath() << "\n";
            }
            else if(plainText.contains(QRegExp("7z.*")))
            {
                if(m_bDebug) std::cout << "Find 7Z archive! on this way :: "<< fInfo.absoluteFilePath().toStdString() << std::endl;
                out << "7ZIP :: " << fInfo.absoluteFilePath() << "\n";
            }
            file.close();
        }
    }
	outFile.close();
	std::cout << "---------------------------------------------------------" << std::endl;

	return true;
};

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskSearchArchive());
}
