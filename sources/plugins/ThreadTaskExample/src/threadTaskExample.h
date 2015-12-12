#ifndef __THREAD_TASK_EXAMPLE_H__
#define __THREAD_TASK_EXAMPLE_H__

#include "coex.h"

class ThredTaskExample : public coex::IThreadTask
{
    Q_OBJECT
    Q_INTERFACES(coex::IThreadTask)

public:
    ThredTaskExample();
    ~ThredTaskExample();
    QString help();
    QString name();
    QString author();
    QString description();

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

#endif // __THREAD_TASK_EXAMPLE_H__
