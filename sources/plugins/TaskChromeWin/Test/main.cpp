#include <QFile>
#include <QtSql>
#include <QRegExp>
#include <QXmlStreamWriter>
#include <QCryptographicHash>

void readandwriteBookmarks();
void prefrences();
void sqlHistory();
void write();


class XMLwriter
{

public:
void write_field(QXmlStreamWriter &xmlWriter,QString sName,QString sValue)
{
    xmlWriter.writeStartElement("field");
    xmlWriter.writeAttribute("name",sName);
    xmlWriter.writeCharacters(sValue);
    xmlWriter.writeEndElement();
}


public:
void writeBookmarks(QString name,QString value,QXmlStreamWriter &xmlWriter,int mode,QString type,QString id)
{
    if (mode==1)
    {
            xmlWriter.setAutoFormatting(true);
            xmlWriter.setAutoFormattingIndent(2);
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("add");
    }

    if (mode==2)
    {
            xmlWriter.writeStartElement("doc");
            /*id=MD5(url+Chrome)*/
            write_field(xmlWriter,"id",id);
            write_field(xmlWriter,"application","Chrome");
            write_field(xmlWriter,"doc_type",type);
            write_field(xmlWriter,"bookmark_url",value);
            write_field(xmlWriter,"bookmark_name",name);
            xmlWriter.writeEndElement();
    }

    if (mode==3)
    {
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
}

void writeHistory(QString name,QString value,QString time,QXmlStreamWriter &xmlWriter,int mode,QString type,QString id)
{
    if (mode==1)
    {
            xmlWriter.setAutoFormatting(true);
            xmlWriter.setAutoFormattingIndent(2);
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("add");
    }

    if (mode==2)
    {
            xmlWriter.writeStartElement("doc");
            /*id = MD5(name+value+time+Chrome)*/
            write_field(xmlWriter,"id",id);
            write_field(xmlWriter,"application","Chrome");
            write_field(xmlWriter,"doc_type",type);
            write_field(xmlWriter,"history_name",name);
            write_field(xmlWriter,"history_url",value);
            write_field(xmlWriter,"history_date",time);
            xmlWriter.writeEndElement();
    }

    if (mode==3)
    {
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }

}

void writeHistoryDownloads(QString name,QString value,QString refferer,QString size,QString time,QXmlStreamWriter &xmlWriter,int mode,QString type,QString id)
{
    if (mode==1)
    {
            xmlWriter.setAutoFormatting(true);
            xmlWriter.setAutoFormattingIndent(2);
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("add");
    }

    if (mode==2)
    {
            xmlWriter.writeStartElement("doc");
            /*id = MD5(download+dowload_url+dowload_time+"Chrome)*/
            write_field(xmlWriter,"id",id);
            write_field(xmlWriter,"application","Chrome");
            write_field(xmlWriter,"doc_type",type);
            write_field(xmlWriter,"download_url",value);
            write_field(xmlWriter,"download_path",name);
            write_field(xmlWriter,"download_start_time",time);
            write_field(xmlWriter,"download_size",size);
            write_field(xmlWriter,"download_refferer",refferer);
            xmlWriter.writeEndElement();
    }

    if (mode==3)
    {
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }

}

void writeHistorySearch(QString value,QXmlStreamWriter &xmlWriter,int mode,QString type,QString id)
{
    if (mode==1)
    {
            xmlWriter.setAutoFormatting(true);
            xmlWriter.setAutoFormattingIndent(2);
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("add");
    }

    if (mode==2)
    {
            xmlWriter.writeStartElement("doc");
            /*id = MD5(keyword_term+"Chrome")*/
            write_field(xmlWriter,"id",id);
            write_field(xmlWriter,"application","Chrome");
            write_field(xmlWriter,"doc_type",type);
            write_field(xmlWriter,"keyword_term",value);
            xmlWriter.writeEndElement();
    }

    if (mode==3)
    {
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }

}

void writePreferences(QString name,QString value,QXmlStreamWriter &xmlWriter,int mode,QString type,QString id)
{
    if (mode==1)
    {
            xmlWriter.setAutoFormatting(true);
            xmlWriter.setAutoFormattingIndent(2);
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("add");
    }

    if (mode==2)
    {
            xmlWriter.writeStartElement("doc");
             /*id = MD5(preferences_param_value+"Chrome")*/
            write_field(xmlWriter,"id",id);
            write_field(xmlWriter,"application","Chrome");
            write_field(xmlWriter,"doc_type",type);
            write_field(xmlWriter,"preferences_param_name",name);
            write_field(xmlWriter,"preferences_param_value",value);
            xmlWriter.writeEndElement();
    }

    if (mode==3)
    {
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }

}

};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDir().mkdir("XML");
    readandwriteBookmarks();
    prefrences();
    sqlHistory();
}

void readandwriteBookmarks()
{
    QFile file1("Bookmarks");
    QRegExp rx("\"(.*)\".*\"(.*)\"");
    if (file1.open(QIODevice::ReadOnly))
    {
        QTextStream stream1(&file1);
        QString str,url,name;

        QString path("XML/bookmarks.xml");
        QFile file(path);
        file.open(QFile::WriteOnly);
        QXmlStreamWriter xmlWriter(&file);
        XMLwriter start;
        start.writeBookmarks(NULL,NULL,xmlWriter,1,NULL,NULL);
        while (!stream1.atEnd())
        {
            str=stream1.readLine();

            if ((str.contains("name",Qt::CaseInsensitive)))
            {
                int pos = 0;
                while ((pos = rx.indexIn(str, pos)) != -1)
                {
                    name = rx.cap(2);
                    pos += rx.matchedLength();
                }
            }

            else if (str.contains("http",Qt::CaseInsensitive))
            {
                int pos = 0;
                while ((pos = rx.indexIn(str, pos)) != -1)
                {
                    url = rx.cap(2);
                    pos += rx.matchedLength();
                    XMLwriter start;
                    QString id = QCryptographicHash::hash((url+"Chrome").toUtf8(), QCryptographicHash::Md5).toHex();
                    start.writeBookmarks(name,url,xmlWriter,2,"bookmarks","bookmark_"+id);
                }
            }
        }
        start.writeBookmarks(NULL,NULL,xmlWriter,3,NULL,NULL);
    }
    else
        qDebug()<<"Error";
    file1.close();

}

void sqlHistory()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("History");
    QString path1("XML/history.xml");
    QString path2("XML/download_history.xml");
    QString path3("XML/search_term.xml");

    QFile file1(path1);
    QFile file2(path2);
    QFile file3(path3);


    file1.open(QFile::WriteOnly);
    file2.open(QFile::WriteOnly);
    file3.open(QFile::WriteOnly);

    QXmlStreamWriter xmlWriter1(&file1),xmlWriter2(&file2),xmlWriter3(&file3);
    XMLwriter start;
    start.writeHistory(NULL,NULL,NULL,xmlWriter1,1,NULL,NULL);
    start.writeHistoryDownloads(NULL,NULL,NULL,NULL,NULL,xmlWriter2,1,NULL,NULL);
    start.writeHistorySearch(NULL,xmlWriter3,1,NULL,NULL);

    if (db.open())
    {
        QSqlQuery query1("SELECT url,title,last_visit_time FROM urls");
        QSqlQuery query2("SELECT downloads.target_path,downloads.referrer,downloads.start_time,downloads.received_bytes,downloads_url_chains.url FROM downloads,downloads_url_chains WHERE downloads.id=downloads_url_chains.id");
        QSqlQuery query3("SELECT DISTINCT term FROM keyword_search_terms");

        while (query1.next())
        {
           QString url = query1.value(0).toString();
           QString title = query1.value(1).toString();
           QString time = query1.value(2).toString();
           QString id = QCryptographicHash::hash((title+url+time+"Chrome").toUtf8(), QCryptographicHash::Md5).toHex();
           start.writeHistory(title,url,time,xmlWriter1,2,"history","history_"+id);
        }

        while (query2.next())
        {
          QString dowload_path = query2.value(0).toString();
          QString dowload_referrer = query2.value(1).toString();
          QString dowload_time = query2.value(2).toString();
          QString dowload_size = query2.value(3).toString();
          QString dowload_url = query2.value(4).toString();

          QString id = QCryptographicHash::hash(("download"+dowload_url+dowload_time+"Chrome").toUtf8(), QCryptographicHash::Md5).toHex();
          start.writeHistoryDownloads(dowload_path,dowload_url,dowload_referrer,dowload_size,dowload_time,xmlWriter2,2,"downloads","download_"+id);
        }

         while (query3.next())
         {
          QString term = query3.value(0).toString();
          QString id = QCryptographicHash::hash((term+"Chrome").toUtf8(), QCryptographicHash::Md5).toHex();
          start.writeHistorySearch(term,xmlWriter3,2,"search_term","keyword_search_term_"+id);
         }
         start.writeHistory(NULL,NULL,NULL,xmlWriter1,3,NULL,NULL);
         start.writeHistoryDownloads(NULL,NULL,NULL,NULL,NULL,xmlWriter2,3,NULL,NULL);
         start.writeHistorySearch(NULL,xmlWriter3,3,NULL,NULL);

    }
}

void prefrences()
{
    QFile file1("Preferences");
    QString path("XML/preferences.xml");
    QFile file2(path);
    file2.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&file2);
    XMLwriter start;
    start.writePreferences(NULL,NULL,xmlWriter,1,NULL,NULL);

    if ((file1.open(QIODevice::ReadOnly)))
    {
        QTextStream stream1(&file1);
        QString str;int i=0;
        while (!stream1.atEnd())
        {
            str=stream1.readLine();
            if ((str.contains("chrome_version",Qt::CaseInsensitive)))
            {
                i++;str.replace( " ", "" );
                QString id = QCryptographicHash::hash((str+"Chrome").toUtf8(), QCryptographicHash::Md5).toHex();
                start.writePreferences("chrome_version",str,xmlWriter,2,"prefences","preference_"+id);
            }
            else if (str.contains("default_directory",Qt::CaseInsensitive))
            {
                i++;str.replace( " ", "" );
                QString id = QCryptographicHash::hash((str+"Chrome").toUtf8(), QCryptographicHash::Md5).toHex();
                start.writePreferences("default_directory_download",str,xmlWriter,2,"prefences","preference_"+id);
            }
            else if ((str.contains("username",Qt::CaseInsensitive)))
            {
                i++;str.replace( " ", "" );
                QString id = QCryptographicHash::hash((str+"Chrome").toUtf8(), QCryptographicHash::Md5).toHex();
                start.writePreferences("username",str,xmlWriter,2,"prefences","preference_"+id);
            }
            if (i==3)
                break;
        }
    }
    else
        qDebug()<<"Error";
    start.writePreferences(NULL,NULL,xmlWriter,3,NULL,NULL);
    file1.close();
    file2.close();
}




