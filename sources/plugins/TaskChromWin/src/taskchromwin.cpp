#include "taskchromwin.h"
#include "writerxml.h"
#define SEC_TO_UNIX_EPOCH 11644473600LL

/*!
    \brief Класс для обработки логов веб браузера Google Chrome
    \author иповской Владислав
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
Вычитывает json файл prefrences Chrome с данными. Преобразует к нужному формату.
\param[out] output Папка в которой лежат собранные данные
\param[in] input Путь к обрабатываемому файлу
*/

void TaskChromWin::prefrences(QString input, QString output)
{
    QFile findPref(input);
    QDateTime setTime = QDateTime::fromString (QString("1970-01-01T00:00:00"), Qt::ISODate);
    QDateTime current = QDateTime::currentDateTime();
    uint msecs = setTime.time().msecsTo(current.time());
    writerXML prefer(output + "/chrome/preferences_"+QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")+(QString::number(msecs))+".xml");

    QRegExp rx("\"(.*)\".*\"(.*)\"");

    QFileInfo f(input);
    QString owner=f.owner();

    if ((findPref.open(QIODevice::ReadOnly)))
    {
        QTextStream stream1(&findPref);
        QString str,str2;

        while (!stream1.atEnd())
        {
            str = stream1.readLine();
            if ((str.contains("chrome_version", Qt::CaseInsensitive)))
            {
                int pos = 0;
                while ((pos = rx.indexIn(str, pos)) != -1)
                {
                    str2 = rx.cap(2);
                    pos += rx.matchedLength();
                }
                prefer.writePreferences("chrome_version", str2,owner);
            }
            else if (str.contains("default_directory", Qt::CaseInsensitive))
            {
                int pos = 0;
                while ((pos = rx.indexIn(str, pos)) != -1)
                {
                    str2 = rx.cap(2);
                    pos += rx.matchedLength();
                }
                prefer.writePreferences("default_directory_download", str2,owner);
            }
            else if ((str.contains("\"username\"", Qt::CaseInsensitive)))
            {
                int pos = 0;
                while ((pos = rx.indexIn(str, pos)) != -1)
                {
                    str2 = rx.cap(2);
                    pos += rx.matchedLength();
                }
                prefer.writePreferences("username", str2,owner);
            }
        }
    }
    else
        qDebug() << "Error";
    findPref.close();
}

/*!
 * \brief TaskChromWin::bookmarks
 * \param input
 * \param output
 */
void TaskChromWin::bookmarks(QString input, QString output)
{
    QDateTime setTime = QDateTime::fromString (QString("1970-01-01T00:00:00"), Qt::ISODate);
    QDateTime current = QDateTime::currentDateTime();
    uint msecs = setTime.time().msecsTo(current.time());

    QFile findBook(input);
    QRegExp rx("\"(.*)\".*\"(.*)\"");
    writerXML bookm(output + "/chrome/bookmarks_"+QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")+(QString::number(msecs))+".xml");

    QFileInfo f1(input);
    QString owner=f1.owner();

    if ((findBook.open(QIODevice::ReadOnly)))
    {
        QTextStream stream1(&findBook);
        QString str, url, name,date,buf;
        while (!stream1.atEnd())
        {
            str = stream1.readLine();
                        if ((str.contains("date_added", Qt::CaseInsensitive)))
                        {
                            int pos = 0;
                            while ((pos = rx.indexIn(str, pos)) != -1)
                            {
                                date = rx.cap(2);
                                pos += rx.matchedLength();
                            }
                            QDateTime dt(QDateTime::fromTime_t((date.toLongLong()/1000000)-SEC_TO_UNIX_EPOCH));
                            buf=dt.toString();
                        }

                        else if ((str.contains("name", Qt::CaseInsensitive)))
                        {
                            int pos = 0;
                            while ((pos = rx.indexIn(str, pos)) != -1)
                            {
                                name = rx.cap(2);
                                pos += rx.matchedLength();
                            }
                        }

                        else if (str.contains("http", Qt::CaseInsensitive))
                        {
                            int pos = 0;
                            while ((pos = rx.indexIn(str, pos)) != -1)
                            {
                                url = rx.cap(2);
                                pos += rx.matchedLength();
                                bookm.writeBookmarks("url",url,name,owner,buf);

                            }
                        }
        }


    }
    else
        qDebug() << "Error";
    findBook.close();

}

/*!
 * \brief TaskChromWin::history
 * \param input
 * \param output
 */
void TaskChromWin::history(QString input, QString output)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(input);

    QDateTime setTime = QDateTime::fromString (QString("1970-01-01T00:00:00"), Qt::ISODate);
    QDateTime current = QDateTime::currentDateTime();
    uint msecs = setTime.time().msecsTo(current.time());

    QFileInfo f1(input);
    QString owner=f1.owner();

    writerXML h1(output + "/chrome/history_"+QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")+(QString::number(msecs))+".xml");
    writerXML h2(output + "/chrome/download_history_"+QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")+(QString::number(msecs))+".xml");
    writerXML h3(output + "/chrome/search_term_"+QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")+(QString::number(msecs))+".xml");

    if (db.open())
    {
           QSqlQuery query1("SELECT url,title,visit_count,datetime(last_visit_time / 1000000 + (strftime('%s', '1601-01-01')), 'unixepoch') FROM urls");
           QSqlQuery query2("SELECT downloads.target_path,downloads.referrer,datetime(downloads.start_time / 1000000 + (strftime('%s', '1601-01-01')), 'unixepoch'),datetime(downloads.end_time / 1000000 + (strftime('%s', '1601-01-01')), 'unixepoch'),downloads.received_bytes,downloads_url_chains.url FROM downloads,downloads_url_chains WHERE downloads.id=downloads_url_chains.id");
           QSqlQuery query3("SELECT DISTINCT term FROM keyword_search_terms");

           while (query1.next())
           {
               QString url = query1.value(0).toString();
               QString title = query1.value(1).toString();
               QString visit_count = query1.value(2).toString();
               QString time = query1.value(3).toString();
               h1.writeHistory(title, url,visit_count,time,owner);
           }

           while (query2.next())
           {
               QString dowload_path = query2.value(0).toString();
               QString dowload_referrer = query2.value(1).toString();
               QString dowload_time_start = query2.value(2).toString();
               QString dowload_time_end = query2.value(3).toString();
               QString dowload_size = query2.value(4).toString();

               int n = (dowload_size.toInt())/1024;
               QString size = (QString::number(n))+"_Kbytes";

               QString dowload_url = query2.value(5).toString();

               h2.writeHistoryDowload(dowload_path, dowload_url, dowload_referrer, size, dowload_time_start,dowload_time_end,owner);
           }

           while (query3.next())
           {
               QString term = query3.value(0).toString();
               h3.writeHistorySearch(term,owner);
           }

     }
}

/*!
 * \brief TaskChromWin::extension
 * \param input
 * \param output
 */
void TaskChromWin::extension(QString input, QString output)
{
    QDateTime setTime = QDateTime::fromString (QString("1970-01-01T00:00:00"), Qt::ISODate);
    QDateTime current = QDateTime::currentDateTime();
    uint msecs = setTime.time().msecsTo(current.time());

    QDirIterator iterator (input, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    QRegExp rx("\"(.*)\".*\"(.*)\"");
    writerXML bookm(output + "/chrome/extensions_"+QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")+(QString::number(msecs))+".xml");


    QFileInfo f1(input);
    QString owner=f1.owner();


    while(iterator.hasNext())
    {
        iterator.next();
        QFileInfo f = iterator.fileInfo();
        if ((f.fileName())=="manifest.json")
        {
            QString str=iterator.fileInfo().absoluteFilePath();
            QFile findext(str);
            if ((findext.open(QIODevice::ReadOnly)))
            {
                QTextStream stream1(&findext);
                QString name;
                while (!stream1.atEnd())
                {
                    str = stream1.readLine();
                    if ((str.contains("\"name\":", Qt::CaseInsensitive)))
                    {
                        int pos = 0;
                        while ((pos = rx.indexIn(str, pos)) != -1)
                        {
                            name = rx.cap(2);
                            pos += rx.matchedLength();
                            bookm.writeExt(name,owner);
                        }
                    }
                }
            }
            findext.close();
        }

    }

}

/*!
 * \brief TaskChromWin::login
 * \param input
 * \param output
 */
void TaskChromWin::login(QString input, QString output)
{
    QDateTime setTime = QDateTime::fromString (QString("1970-01-01T00:00:00"), Qt::ISODate);
    QDateTime current = QDateTime::currentDateTime();
    uint msecs = setTime.time().msecsTo(current.time());

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(input);

    QFileInfo f1(input);
    QString owner=f1.owner();

    writerXML log(output + "/chrome/login_"+QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")+(QString::number(msecs))+".xml");
    if (db.open())
    {
        QSqlQuery query("SELECT action_url,username_value,datetime(date_created/ 1000000 + (strftime('%s', '1601-01-01')), 'unixepoch') FROM logins");
        while (query.next())
        {
            QString url = query.value(0).toString();
            QString login = query.value(1).toString();
            QString date_created = query.value(2).toString();
            log.writeLogin(url,login,date_created,owner);
        }
    }
}

/*!
 * \brief TaskChromWin::execute
 * \param config
 * \return
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

    QRegExp chromePrefPath(".*Preferences$");
    QRegExp chromeBookPath(".*Bookmarks$");
    QRegExp chromeHistoryPath(".*History$");
    QRegExp chromeExtPath(".*Extensions$");
    QRegExp chromeLoginPath(".*LoginData$");

    TaskChromWin pref,book,hist,ext,log;
    QDirIterator dirPath(config->inputFolder(), QDir::Files |QDir::Dirs| QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
    while (dirPath.hasNext())
    {
        if (m_bDebug)qDebug() << dirPath.filePath();

        if (dirPath.filePath().contains(chromePrefPath))
        {
            pref.prefrences(dirPath.filePath(), config->outputFolder());
        }
        else if (dirPath.filePath().contains(chromeBookPath))
        {
            book.bookmarks(dirPath.filePath(), config->outputFolder());
        }
        else if (dirPath.filePath().contains(chromeHistoryPath))
        {
            hist.history(dirPath.filePath(), config->outputFolder());
        }
        else if (dirPath.filePath().contains(chromeExtPath))
        {
            ext.extension(dirPath.filePath(), config->outputFolder());
        }
        else if (dirPath.filePath().contains(chromeLoginPath))
        {
            log.login(dirPath.filePath(), config->outputFolder());
        }
        dirPath.next();
    }


    return true;
}

coex::ITask* createTask()
{
    return (coex::ITask*)(new TaskChromWin());
}
