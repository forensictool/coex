#ifndef __TASK_SEARCH_PROGRAMM_WIN_H__
#define __TASK_SEARCH_PROGRAMM_WIN_H__

#include "../coex/task.h"
#include <QXmlStreamWriter>
#include <QString>
#include <QMap>

class taskSearchProgrammWin : public coex::task 
{
	public:
		taskSearchProgrammWin();
        virtual ~taskSearchProgrammWin();
	
		// coex::Task
		virtual QString manual();
        virtual void setOption(QStringList options);
		virtual QString command();
		virtual bool supportOS(const coex::typeOS &os);
		virtual QString name();
		virtual QString description();
		virtual bool test();
		virtual bool execute(const coex::config &config);
		
		// other
		void recourceDirs(	QString baseFolder, 
			QString parentFolder, 
			QString dirStr, 
			QXmlStreamWriter* xmlWrite, 
			int &id, 
			int depth = 0, 
			int maxdepth = 5
		);
        // QStringList getSubDirs(QString dirStr);
		
	private:
		QString m_strName;
		QString m_strDescription;
        bool m_bDebug;
        QStringList m_qslExcept;
        QStringList m_qslDirs;
        QMap<QString, QString> m_mapProgInfo;
};

#endif // __TASK_SEARCH_PROGRAMM_WIN_H__
