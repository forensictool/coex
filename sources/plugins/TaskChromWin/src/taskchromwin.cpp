#include "taskchromwin.h"
#include "writerxml.h"
/*!
    \brief Класс для обработки логов веб браузера Google Chrome
    \author ----
    \version 1.0
    \date Март 2015 года
    \warning Данный класс создан только в учебных целях

    Обычный дочерний класс, который отнаследован от ранее созданного класса coex
*/
TaskChromWin::TaskChromWin()
{
    m_bDebug = false;
};

QString TaskChromWin::help()
{
    return "\t--debug - viewing debug messages";
};

QString TaskChromWin::name()
{
    return "ChromWin";
};

QString TaskChromWin::author()
{
    return "Vlad Shipovskoy";
};

QString TaskChromWin::description()
{
    return "Task is search logs of Browser Chrome for WINDOWS";
};

bool TaskChromWin::isSupportOS(const coex::ITypeOperationSystem *os)
{
    return (os->platform() == "Windows" && (os->version() == "XP" || os->version() == "7"));
};

void TaskChromWin::setOption(QStringList options)
{
    /*
    *
    * */
    if (options.contains("--debug"))
        m_bDebug = true;
};

/*!
Вычитывает xml файл prefrences Chrome с данными. Преобразует к нужному формату.
\param[out] output Папка в которой лежат собранные данные
\param[in] input Путь к обрабатываемому файлу
*/

void TaskChromWin::prefrences(QString input, QString output)
{
    QFile findPref(input);
    writerXML prefer(output + "/chrome/preferences.xml");
    if ((findPref.open(QIODevice::ReadOnly))) {
        QTextStream stream1(&findPref);
        QString str;
        int i = 0;

        while (!stream1.atEnd()) {
            str = stream1.readLine();
            if ((str.contains("chrome_version", Qt::CaseInsensitive))) {
                prefer.writePreferences("chrome_version", str);
                i++; str.replace(" ", "");
            } else if (str.contains("default_directory", Qt::CaseInsensitive)) {
                prefer.writePreferences("default_directory_download", str);
                i++; str.replace(" ", "");
            } else if ((str.contains("username", Qt::CaseInsensitive))) {
                prefer.writePreferences("username", str);
                i++; str.replace(" ", "");
            }
            if (i == 3)
                break;
        }
    } else
        qDebug() << "Error";
    findPref.close();
}
/*!
Некий main класса TaskChromWin
\param[in] config конфиг с путями входными, выходными
\return Возвращает статус исполнения таска
*/
bool TaskChromWin::execute(const coex::IConfig *config)
{
    if (m_bDebug) {
        qDebug() << "==========TaskChromWin::execute==========\n\n";
        qDebug() << "Debug mode ON\n";
        qDebug() << "InputFolder: " << config->inputFolder() << "\n";
    };

    QDir dir(config->outputFolder());
    dir.mkdir("chrome");

    QRegExp chromePrefPath(".*Preference");
    /*QRegExp pidginPathContact(".*purple/blist.xml");
    QRegExp pidginPathLogHtml(".*purple/logs.*html");
    QRegExp pidginPathLogTxt(".*purple/logs.*txt");*/

    TaskChromWin pref;
    QDirIterator dirPath(config->inputFolder(), QDir::Files | QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
    while (dirPath.hasNext()) {
        qDebug() << dirPath.filePath();
        if (dirPath.filePath().contains(chromePrefPath)) {
            pref.prefrences(dirPath.filePath(), config->outputFolder());

        }
        dirPath.next();
    }
    return true;
}

coex::ITask* createTask()
{
    return (coex::ITask*)(new TaskChromWin());
}
