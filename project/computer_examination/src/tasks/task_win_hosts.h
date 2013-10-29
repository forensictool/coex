#ifndef __TASK_SEARCH_SYSLOGS_WIN_H__
#define __TASK_SEARCH_SYSLOGS_WIN_H__

#include "../coex/task.h"

class taskSearchHosts : public coex::task 
{
	public:
    taskSearchHosts();
    virtual ~taskSearchHosts();
	
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
    QString findFileHosts(QString dir);
		
	private:
		QString m_strName;
		QString m_strDescription;
    bool m_bDebug;
};

#endif // __TASK_SEARCH_SYSLOGS_WIN_H__
