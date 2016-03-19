#include "taskMessengers.h"
#include "writerMessages.h"
#include "XMLReader_ICQContacts.h"

#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QDebug>
#include <QStringList>

TaskMessengers::TaskMessengers() : m_pbDebug(false)
{

}

TaskMessengers::~TaskMessengers(){}

QString TaskMessengers::help()
{
    return "\t--debug - viewing debug messages";
}

QString TaskMessengers::name()
{
    return "ICQ";
}

QString TaskMessengers::author()
{
    return "Marina Meyta";
}

QString TaskMessengers::description()
{
    return "messengers task";
}

bool TaskMessengers::isSupportOS(const coex::ITypeOperationSystem *os)
{
    return (os->platform() == "Windows");
}

void TaskMessengers::setOption(QStringList options)
{
    if(options.contains("--debug"))
        m_pbDebug = true;
}

void TaskMessengers::init(const coex::IConfig *config)
{
    m_pConfig = config;
    m_pbDebug = m_pConfig->isDebugEnable();
}

bool TaskMessengers::execute()
{
    if(m_pbDebug) {
        qDebug() << "DEBUG MOD";
        qDebug() << QString("Input folder %1").arg(m_pConfig->inputFolder());
        qDebug() << QString("Output folder %1").arg(m_pConfig->outputFolder());
    };

    XMLReader_ICQContacts reader; // создаем экземпляр класса
    reader.read(m_pConfig->inputFolder() + "/Users/Default/AppData/Roaming/test.xml", m_pConfig->outputFolder());

    return true;
}

coex::IThreadTask* createThreadTask()
{
    return (new TaskMessengers());
}
