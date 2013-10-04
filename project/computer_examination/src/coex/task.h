#ifndef __TASK_H__
#define __TASK_H__

#include <QString>
#include <QStringList>
#include <QVector>

namespace coex
{
	enum typeOS
	{
		ceUnknown,
		ceLinux,
		ceWindows95,
		ceWindows98,
		ceWindowsXP,
		ceWindowsVista,
		ceWindows7,
		ceWindows8
	};
	
	struct config
	{
    config() 
    { 
      os = coex::ceUnknown;
    };

		QString inputFolder;
		QString outputFolder;
		typeOS os;
	};

	class task
	{
		public:
			virtual QString manual() = 0;
			virtual void setOption(QStringList) = 0;
			virtual QString command() = 0;
			virtual bool supportOS(const coex::typeOS &os) = 0;
			virtual QString name() = 0;
			virtual QString description() = 0;
			virtual bool test() = 0;
			virtual bool execute(const coex::config &config) = 0;
	};
	
	template<typename T>
	bool createTask(coex::typeOS os, QVector<coex::task*> &tasks, bool bNeedAll)
	{
		T* t = new T();
		if(t->supportOS(os) || bNeedAll)
			tasks << (coex::task *)t;
		else
		{
			delete t;
			t = NULL;
		}
		return (t != NULL);
	};
}


#endif // __TASK_H__
