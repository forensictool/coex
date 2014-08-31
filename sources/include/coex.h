#ifndef __COEX_H__
#define __COEX_H__

#include <QString>
#include <iostream>

namespace coex
{
	class ITypeOperationSystem {
		virtual QString platform() = 0;
		/* example returned: "windows" or "linux" */
		
		virtual QString version() = 0;
		/* example returned:
		 * if platform is "windows" then "95" or "98" or "XP" or "Vista" or "7" or "8"
		 * */
		
		virtual QString toString() = 0;
		/*
		 *
		 * */

		virtual bool isUnknown() = 0;
		virtual bool isWindows() = 0;
		virtual bool isLinux() = 0;
		virtual void copyTo(coex::ITypeOperationSystem *) = 0;
	};
	
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

	/* interface for
	 * config object 
	 * */
	class IConfig {
		public:
			virtual QString inputFolder() = 0;
			virtual QString outputFolder() = 0;
			virtual coex::ITypeOperationSystem* typeOS() = 0;
			
			virtual void setInputFolder(QString path) = 0;
			virtual void setOutputFolder(QString path) = 0;
			virtual void setTypeOS(coex::ITypeOperationSystem*) = 0;
	};
	
	/* interface for
	 * detect operation system 
	 * must be TODO */
	class IDetectOperationSystem {
		public:
			virtual coex::ITypeOperationSystem* detect(QString path) = 0;
			virtual QString name() = 0;
			virtual QString author() = 0;
	};

	class ITask
	{
		public:
			virtual QString manual() = 0;
			virtual void setOption(QStringList) = 0;
			virtual QString command() = 0;
			virtual bool isSupportOS(const coex::ITypeOperationSystem *os) = 0;
			virtual QString name() = 0;
			virtual QString author() = 0;
			virtual QString description() = 0;
			virtual bool test() = 0;
			virtual bool execute(const coex::IConfig *config) = 0;
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
}

#endif //__COEX_H__
