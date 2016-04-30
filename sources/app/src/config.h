#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "coex.h"
#include "hdd.h"
#include <QString>
#include <QMap>
#include <iostream>

class Config : coex::IConfig {
	public:
		Config();
		virtual QString inputFolder() const ;
		virtual QString outputFolder() const ;
		virtual const  coex::ITypeOperationSystem* typeOS() const ;

		virtual void setInputFolder(QString path);
		virtual void setOutputFolder(QString path);
		virtual void setTypeOS(coex::ITypeOperationSystem* pTypeOS);

		virtual bool isUnknownOS();
		virtual bool isWindows();
		virtual bool isLinux();

		//parse Arguments
		virtual bool getArgumentsValues(int, char **, QString);
		virtual bool isDebugEnable() const ;

        Hdd *parsedHdd;

	private:
		coex::ITypeOperationSystem* m_pTypeOS;
		QString m_sInputFolder;
		QString m_sOutputFolder;
		QMap<QString, QString> m_qmArguments;
};

coex::IConfig* createConfig();


#endif //__CONFIG_H__
