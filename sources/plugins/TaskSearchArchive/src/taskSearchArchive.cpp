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
    m_bDebug = true;
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
    outDirStr.append("/Result");
	QDir().mkdir(outDirStr);
    outDirStr.append("/Result.txt");
	QFile outFile(outDirStr);
	if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text)&&(m_bDebug))
	{
		std::cout << "ERROR: can't open output file" << std::endl;
        return false;
	}
	QTextStream out(&outFile);
	QDirIterator fileListDirit(dirStr, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
	QStringList buf;
	while(fileListDirit.hasNext())
	{
		QString str = QString("%1").arg(fileListDirit.next());
        QFileInfo fInfo(str);
        if(m_bDebug) std::cout << fInfo.absoluteFilePath().toStdString() << std::endl;
        QFile file(fInfo.absoluteFilePath());
        /*if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString plainText = file.readLine().trimmed();
            QString hexText = QByteArray::fromHex(file.readLine().trimmed());
            QString reading = file.read(8);

            while(!file.)
            {
                str = file.readLine();
                QStringList list = str.split(QRegExp("\\W+"), QString::SkipEmptyParts);
                for(int i = 0; i < list.count(); i++)
                {
                    str = list.at(i);
                    if(buf.indexOf(str) == -1)
                    {
                        buf.append(str);
                    }
                }
            }
            if(m_bDebug) std::cout << ":::::: "<< reading.toStdString() <<":::::"<< std::endl;
            if(m_bDebug) std::cout << ":::::: "<< plainText.toStdString() <<":::::"<< std::endl;
            if(m_bDebug) std::cout << ":::::: "<< hexText.toStdString()   <<":::::"<< std::endl;
            file.close();
        }*/
    }
	buf.sort();
	for(int i = 0; i < buf.count(); i++)
	{
		out << buf.at(i) << "\n";
	}
	outFile.close();
	std::cout << "---------------------------------------------------------" << std::endl;

	return true;
};

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskSearchArchive());
}
