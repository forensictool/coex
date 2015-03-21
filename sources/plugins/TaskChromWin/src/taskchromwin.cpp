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
    if ((findPref.open(QIODevice::ReadOnly)))
    {
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
    }
    else
        qDebug() << "Error";
    findPref.close();
}
/*!
Некий main класса TaskChromWin
\param[in] config конфиг с путями входными, выходными
\return Возвращает статус исполнения таска
*/

void TaskChromWin::bookmarks(QString input, QString output)
{
    QFile findBook(input);
    QRegExp rx("\"(.*)\".*\"(.*)\"");
    writerXML bookm(output + "/chrome/bookmarks.xml");
    if ((findBook.open(QIODevice::ReadOnly)))
    {
        QTextStream stream1(&findBook);
        QString str, url, name;
        while (!stream1.atEnd())
        {
            str = stream1.readLine();

                        if ((str.contains("name", Qt::CaseInsensitive)))
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
                                bookm.writeBookmarks("url",url,name);

                            }
                        }
        }


    }
    else
        qDebug() << "Error";
    findBook.close();

}

void TaskChromWin::history(QString input, QString output)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(input);

    writerXML h1(output + "/chrome/history.xml");
    writerXML h2(output + "/chrome/download_history.xml");
    writerXML h3(output + "/chrome/search_term.xml");

    if (db.open())
    {
           QSqlQuery query1("SELECT url,title,datetime(last_visit_time / 1000000 + (strftime('%s', '1601-01-01')), 'unixepoch') FROM urls");
           QSqlQuery query2("SELECT downloads.target_path,downloads.referrer,datetime(downloads.start_time / 1000000 + (strftime('%s', '1601-01-01')), 'unixepoch'),datetime(downloads.end_time / 1000000 + (strftime('%s', '1601-01-01')), 'unixepoch'),downloads.received_bytes,downloads_url_chains.url FROM downloads,downloads_url_chains WHERE downloads.id=downloads_url_chains.id");
           QSqlQuery query3("SELECT DISTINCT term FROM keyword_search_terms");

           while (query1.next())
           {
               QString title = query1.value(1).toString();
               QString url = query1.value(0).toString();
               QString time = query1.value(2).toString();
               h1.writeHistory(title, url, time);
           }

           while (query2.next())
           {
               QString dowload_path = query2.value(0).toString();
               QString dowload_referrer = query2.value(1).toString();
               QString dowload_time_start = query2.value(2).toString();
               QString dowload_time_end = query2.value(3).toString();
               QString dowload_size = query2.value(4).toString();
               QString dowload_url = query2.value(5).toString();
               h2.writeHistoryDowload(dowload_path, dowload_url, dowload_referrer, dowload_size, dowload_time_start,dowload_time_end);
           }

           while (query3.next())
           {
               QString term = query3.value(0).toString();
               h3.writeHistorySearch(term);
           }

     }
}



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
    QRegExp chromeBookPath(".*Bookmark");
    QRegExp chromeHistoryPath(".*Histor");
    /*QRegExp pidginPathContact(".*purple/blist.xml");
    QRegExp pidginPathLogHtml(".*purple/logs.*html");
    QRegExp pidginPathLogTxt(".*purple/logs.*txt");*/

    TaskChromWin pref,book,hist;
    QDirIterator dirPath(config->inputFolder(), QDir::Files | QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
    while (dirPath.hasNext())
    {
        qDebug() << dirPath.filePath();
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

        dirPath.next();
    }


    return true;
}

coex::ITask* createTask()
{
    return (coex::ITask*)(new TaskChromWin());
}
