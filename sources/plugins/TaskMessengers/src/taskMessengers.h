#ifndef __TASK_MESSENGERS_H__
#define __TASK_MESSENGERS_H__

#include "coex.h"

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>


class TaskMessengers : public coex::IThreadTask
{
    Q_OBJECT
    Q_INTERFACES(coex::IThreadTask)

    public:
        TaskMessengers();
        ~TaskMessengers();
        virtual QString help();
        virtual QString name();
        virtual QString author();
        virtual QString description();
        /*!
         * \brief isSupportOS
         * \param os
         * \return
         */

        bool isSupportOS(const coex::ITypeOperationSystem *os);
        void setOption(QStringList);
        void init(const coex::IConfig *config);

    public slots:
        bool execute();

    private:
        bool m_pbDebug;
        const coex::IConfig *m_pConfig;
};

extern "C"
{
    coex::IThreadTask* createThreadTask();
}

#endif // __TASK_MESSENGERS_H__
