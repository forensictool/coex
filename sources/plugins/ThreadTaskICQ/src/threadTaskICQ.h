#ifndef __THREAD_TASK_ICQ_H__
#define __THREAD_TASK_ICQ_H__

#include "coex.h"

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>


class ThreadTaskICQ : public coex::IThreadTask
{
    Q_OBJECT
    Q_INTERFACES(coex::IThreadTask)

    public:
        ThreadTaskICQ();
        ~ThreadTaskICQ();
        virtual QString help();
        virtual QString name();
        virtual QString author();
        virtual QString description();

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

#endif // __THREAD_TASK_ICQ_H__
