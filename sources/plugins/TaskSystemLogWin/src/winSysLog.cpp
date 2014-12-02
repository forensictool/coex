#include "winSysLog.h"
#include "reader.h"

#include <QStringList>
#include <QDir>
#include <QDirIterator>

TaskSystemLogWin::TaskSystemLogWin() {
	m_bDebug = false;
};

QString TaskSystemLogWin::help() {
	return "\t--debug - viewing debug messages";
};

QString TaskSystemLogWin::name() {
	return "SystemLogWin";
};

QString TaskSystemLogWin::author() {
	return "Dmitrii Nikiforov";
};

QString TaskSystemLogWin::description() {
	return "Task is search system log in Windows";
};

bool TaskSystemLogWin::isSupportOS(const coex::ITypeOperationSystem *os) {
	return (os->platform() == "Windows");
};

void TaskSystemLogWin::setOption(QStringList options) {
	/*
	 * 
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};

bool TaskSystemLogWin::execute(const coex::IConfig *config) {

	QStringList* evtFiles = new QStringList();

	QString dirStr(config->inputFolder());
	dirStr += "/WINDOWS";
	QDirIterator dirit(dirStr, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    try
    {
    	while(dirit.hasNext())
        {
        	QString str = QString("%1").arg(dirit.next());
            QStringList buf = str.split("/", QString::SkipEmptyParts);
            buf = buf.at(buf.size() - 1).split(".", QString::SkipEmptyParts);
            if (buf.at(buf.size() - 1).toLower() == "evt")
            {
                *evtFiles << str;
            }
        }
    }
    catch(...)
    {
        //if(m_bDebug) std::cout << "OOOOPS!" << std::endl;
    }

    /*for(int i = 0; i < evtFiles->count(); i++)
    	std::cout << evtFiles->at(i).toStdString() << std::endl;*/

    readEvtFiles(*evtFiles, config);
    delete evtFiles;

	/*if(m_bDebug)
      std::cout << "!!!>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;*/

	return true;
}

coex::ITask* createTask() {
	return (coex::ITask*)(new TaskSystemLogWin());
}
