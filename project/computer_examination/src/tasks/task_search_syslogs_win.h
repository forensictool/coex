#ifndef __TASK_SEARCH_SYSLOGS_WIN_H__
#define __TASK_SEARCH_SYSLOGS_WIN_H__

#include "../coex/task.h"

class taskSearchSyslogsWin : public coex::task 
{
	public:
		taskSearchSyslogsWin();
        virtual ~taskSearchSyslogsWin();

		// coex::Task
		virtual QString manual();
        virtual void setOption(QStringList options);
		virtual QString command();
		virtual bool supportOS(const coex::typeOS &os);
		virtual QString name();
		virtual QString description();
		virtual bool test();
		virtual bool execute(const coex::config &config);
        virtual void readLogFiles(QStringList logFiles, const coex::config& config);
        virtual void readEvtFiles(QStringList evtFiles, const coex::config& config);
		
	private:
		QString m_strName;
		QString m_strDescription;
        bool m_bDebug;
};

#endif // __TASK_SEARCH_SYSLOGS_WIN_H__
