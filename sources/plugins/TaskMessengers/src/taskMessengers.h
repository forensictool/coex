#ifndef __TASK_MESSENGERS_H__
#define __TASK_MESSENGERS_H__

#include "coex.h"

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>


class TaskMessengers : coex::ITask
{
	public:
		TaskMessengers();
		virtual QString help();
		virtual QString name();
		virtual QString author();
		virtual QString description();
        /*!
         * \brief isSupportOS
         * \param os
         * \return 
         */
		virtual bool isSupportOS(const coex::ITypeOperationSystem *os);
		virtual void setOption(QStringList);
		virtual bool execute(const coex::IConfig *config);
	private:
		bool m_bDebug;
};

extern "C"
{
	coex::ITask* createTask();
}

#endif // __TASK_MESSENGERS_H__
