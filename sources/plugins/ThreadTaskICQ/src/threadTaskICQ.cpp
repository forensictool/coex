#include "threadTaskICQ.h"
#include "writerMessages.h"
#include "XMLReader_ICQContacts.h"

#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QDebug>
#include <QDirIterator>

ThreadTaskICQ::ThreadTaskICQ() : m_pbDebug(false)
{

}

ThreadTaskICQ::~ThreadTaskICQ(){}

QString ThreadTaskICQ::help()
{
    return "\t--debug - viewing debug messages";
}

QString ThreadTaskICQ::name()
{
    return "ICQ";
}

QString ThreadTaskICQ::author()
{
    return "Marina Meyta";
}

QString ThreadTaskICQ::description()
{
    return "ICQ task for parsing XML-files with ICQ contacts";
}

bool ThreadTaskICQ::isSupportOS(const coex::ITypeOperationSystem *os)
{
    return (os->platform() == "Windows");
}

void ThreadTaskICQ::setOption(QStringList options)
{
    if(options.contains("--debug"))
        m_pbDebug = true;
}

void ThreadTaskICQ::init(const coex::IConfig *config)
{
    m_pConfig = config;
    m_pbDebug = m_pConfig->isDebugEnable();
}

bool ThreadTaskICQ::execute()
{
    if(m_pbDebug)
    {
        qDebug() << "DEBUG MOD";
        qDebug() << QString("Input folder %1").arg(m_pConfig->inputFolder());
        qDebug() << QString("Output folder %1").arg(m_pConfig->outputFolder());
    };

    QString dirStr(m_pConfig->inputFolder());
    QString outDirStr(m_pConfig->outputFolder());
    QDirIterator fileListDirit(dirStr, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    while(fileListDirit.hasNext())
    {
        QString str = QString("%1").arg(fileListDirit.next());
        QFileInfo fInfo(str);
        if(fInfo.suffix() == "xml")
        {
//            qDebug() << QString("fInfo.absoluteFilePath() = ").arg(fInfo.absoluteFilePath());
            // парсинг XML-файла с контактами
            XMLReader_ICQContacts reader; // создаем экземпляр класса
            reader.read(fInfo.absoluteFilePath(), outDirStr);
        }
    }

    return true;
}

coex::IThreadTask* createThreadTask()
{
    return (new ThreadTaskICQ());
}
