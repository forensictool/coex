#ifndef __EXAMPLE_TASKS_H__
#define __EXAMPLE_TASKS_H__

#include "../coex/task.h"

class exampleTask : public coex::task 
{
	public:
        exampleTask();
        virtual ~exampleTask();
	
		// coex::Task 
		virtual QString manual();
		virtual void setOption(QStringList list);
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

#endif // __EXAMPLE_TASKS_H__
