#ifndef __TASK_DETECT_OS_H__
#define __TASK_DETECT_OS_H__

#include "../coex/task.h"

class taskDetectOs : public coex::task 
{
	public:
		taskDetectOs();
	
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
};

#endif // __TASK_DETECT_OS_H__
