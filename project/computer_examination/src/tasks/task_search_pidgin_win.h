#ifndef __TASK_SEARCH_PIDGIN_WIN_H__
#define __TASK_SEARCH_PIDGIN_WIN_H__

#include "../coex/task.h"

class taskSearchPidginWin : public coex::task 
{
	public:
		taskSearchPidginWin();
	
		// coex::Task
		virtual QString manual();
		virtual void setOption(QStringList);
		virtual QString command(); 
		virtual bool supportOS(const coex::typeOS &os);
		virtual QString name();
		virtual QString description();
		virtual bool test();
		virtual bool execute(const coex::config &config);
		
	private:
		QString m_strName;
		QString m_strDescription;
		bool m_bDebug;
};

#endif // __TASK_SEARCH_PIDGIN_WIN_H__
