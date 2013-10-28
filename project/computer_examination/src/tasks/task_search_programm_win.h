#ifndef __TASK_SEARCH_PROGRAMM_WIN_H__
#define __TASK_SEARCH_PROGRAMM_WIN_H__

#include "../coex/task.h"

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
        virtual QStringList getSubDirs(QString dirStr);
		
	private:
		QString m_strName;
		QString m_strDescription;
        bool m_bDebug;
        QStringList m_qslExcept = (QStringList()
                                   << "."
                                   << ".."
                                   << "Common Files"
                                   << "Microsoft Analysis Services"   /*???*/
                                   << "MSBuild"
                                   << "Windows NT"
                                   << "WindowsUpdate"
                                   );
        QStringList m_qslDirs = (QStringList()
                                 << "AVAST Software"
                                 << "Oracle"
                                 << "Games"
                                 << "ubisoft"
                                 << "Microsoft Office"
                                 );
};

#endif // __TASK_SEARCH_PROGRAMM_WIN_H__
