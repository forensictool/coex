#include "parseHdd.h"
#include "hdd.h"

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

    QDirIterator dirPath(config->inputFolder(), QDir::Files |QDir::Dirs| QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
    QList<QDir> dirlist;
    dirlist.append(QDir(config->inputFolder()));

    while (dirPath.hasNext())
    {
        dirlist.append(QDir(dirPath.next()));
    }

//    Hdd storedhdd(dirlist);
//    QString wildcard = "*.jpg";
//    QFileInfoList outputlist = storedhdd.getFiles(wildcard);
//    foreach(QFileInfo file, outputlist){
//        qDebug() << file.absoluteFilePath();
//    }

	return true;
};

coex::ITask* createTask() {
    return (coex::ITask*)(new TaskParseHDD());
}
