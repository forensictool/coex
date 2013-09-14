#ifndef __TASK_H__
#define __TASK_H__

#include <QString>
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
			virtual bool supportOS(const coex::typeOS &os) = 0;
			virtual QString name() = 0;
			virtual QString description() = 0;
			virtual bool test() = 0;
			virtual bool execute(const coex::config &config) = 0;
	};
	
	template<typename T>
	bool createTask(coex::typeOS os, QVector<coex::task*> &tasks)
	{
		T* t = new T();
		if(t->supportOS(os))
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
