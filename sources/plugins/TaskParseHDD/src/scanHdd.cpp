#include "parseHdd.h"

#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>
#include <QDirIterator>

TaskParseHDD::TaskParseHDD() {
	m_bDebug = false;
};

QString TaskParseHDD::help() {
	return "\t--debug - viewing debug messages";
};

QString TaskParseHDD::name() {
    return "ParseHDD";
};

QString TaskParseHDD::author() {
    return "Ilya Bokov";
};

QString TaskParseHDD::description() {
    /* DONT FORGET TO ADD DESCRIPTION */
    return "later";
};

bool TaskParseHDD::isSupportOS(const coex::ITypeOperationSystem *os) {
	return (os->platform() == "Windows");
};

void TaskParseHDD::setOption(QStringList options) {
	/*
	 * 
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};

bool TaskParseHDD::execute(const coex::IConfig *config) {
	if(m_bDebug) {
		std::cout << "  !!! debug mode on.\n";
		std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
	};

    qDebug() << "it's working!";

    QDirIterator dirPath(config->inputFolder(), QDir::Files |QDir::Dirs| QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
    QString filename=config->outputFolder().append("Data.txt");
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        while (dirPath.hasNext())
        {
            QFileInfo info(dirPath.filePath());
            QString path = info.absoluteFilePath();
            stream << path << endl;
            dirPath.next();
        }
    }

	return true;
};

coex::ITask* createTask() {
    return (coex::ITask*)(new TaskParseHDD());
}
