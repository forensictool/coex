#include "threadTaskExample.h"

#include <QDebug>
#include <QStringList>

ThredTaskExample::ThredTaskExample() : m_pbDebug(false)
{

}

ThredTaskExample::~ThredTaskExample(){}

QString ThredTaskExample::help()
{
    return "\tthis is help message";
}

QString ThredTaskExample::name()
{
    return "ThreadTaskExample";
}

QString ThredTaskExample::author()
{
    return "Firstname Lastname";
}

QString ThredTaskExample::description()
{
    return "\tthis is description";
}

bool ThredTaskExample::isSupportOS(const coex::ITypeOperationSystem *os)
{
    return (os->platform() == "Windows");
}

void ThredTaskExample::setOption(QStringList options)
{
    if(options.contains("--debug"))
        m_pbDebug = true;
};

void ThredTaskExample::init(const coex::IConfig *config)
{
    m_pConfig = config;
    m_pbDebug = m_pConfig->isDebugEnable();
}

bool ThredTaskExample::execute()
{
    qDebug() << "Executing ThreadTaskExample . . .";
    if(m_pbDebug)
    {
        qDebug() << "DEBUG MOD";
        qDebug() << QString("Input folder %1").arg(m_pConfig->inputFolder());
        qDebug() << QString("Output folder %1").arg(m_pConfig->outputFolder());
    }

    return true;
}

coex::IThreadTask* createThreadTask()
{
    return (new ThredTaskExample());
}
