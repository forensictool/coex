#include "taskViber.h"

TaskViber::TaskViber() {
    m_bDebug = false;
};

QString TaskViber::help() {
    return "\t--debug - viewing debug messages";
};

QString TaskViber::name() {
    return "Viber";//
};

QString TaskViber::author() {
    return "Kucher Maxim";//
};

QString TaskViber::description() {
    return "example task";//
};

bool TaskViber::isSupportOS(const coex::ITypeOperationSystem *os) {
    return (os->platform() == "Windows" && (os->version() == "XP" || os->version() == "7" || os->version() == "8"));
};

void TaskViber::setOption(QStringList options) {
    /*
     *
     * */
    if(options.contains("--debug"))
        m_bDebug = true;
};

using namespace std;


void CopyFile(QString filename, QString dir)
{
    QFileInfo fileInfo(filename);
    QString destinationFile = dir + "/" + fileInfo.fileName();

    QFile::copy(filename, destinationFile);
}


void Viber_Avatars(QString Avatars, QString katvib, QString output)
{
    if (!(QDir(output + "/Viber/" + katvib + "/Avatars").exists()==true) )
        {
            QDir().mkdir(output + "/Viber/" + katvib + "/Avatars");
        }

    QString line="";
    QString avat = output + "/Viber/" + katvib + "/Avatars";
    QDir dir(Avatars);
    bool ok = dir.exists();
    if (ok)
    {
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::Name);
        QFileInfoList list = dir.entryInfoList();

        for (int i = 0; i < list.size(); ++i)
        {
            QFileInfo fileInfo = list.at(i);
            line = fileInfo.filePath();
            CopyFile(line, avat);
        }
    }
}


void Viber_Thumbnails(QString thumbnails, QString katvib, QString output)
{
    if (!(QDir(output + "/Viber/" + katvib + "/Thumbnails").exists()==true) )
        {
            QDir().mkdir(output + "/Viber/" + katvib + "/Thumbnails");
        }

    QString line="";
    QString thum = output + "/Viber/" + katvib + "/Thumbnails";
    QDir dir(thumbnails);
    bool ok = dir.exists();
    if (ok)
    {
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::Name);
        QFileInfoList list = dir.entryInfoList();

        for (int i = 0; i < list.size(); ++i)
        {
            QFileInfo fileInfo = list.at(i);
            line = fileInfo.filePath();
            CopyFile(line, thum);
        }
    }
}


void Viber_XP_7_8_10(QString input, QString out, QString output)
{

    if (!(QDir(output + "/Viber").exists()==true) )
        {
            QDir().mkdir(output + "/Viber");
        }

if (!(QDir(output + "/Viber" + out).exists()==true) )
    {
        QDir().mkdir(output + "/Viber/" + out);
    }

QString Pathtemp = output + "/Viber/" + out;

QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
dbase.setDatabaseName(input);
if (dbase.open())
    {

    QSqlQuery query;

    if (query.exec("Select ContactRelation.Number, Contact.FirstName from ContactRelation, Contact where Contact.ContactID = ContactRelation.ContactID"))
    {
        ofstream f;
        f.open(Pathtemp.toUtf8() + "/Phone book.txt");
        if (f)
        {
            QSqlRecord rec = query.record();
            QString    nNumber;
            QString    strName;

            while (query.next())
            {
                nNumber  = query.value(rec.indexOf("Number")).toString();
                strName  = query.value(rec.indexOf("FirstName")).toString();

                if ((nNumber != "") && (strName != ""))
                    f << nNumber.toStdString() << " " << strName.toStdString() << ";\n";

            }
        }
        f.close();
    }

    QSqlQuery query2;

    if (query2.exec("Select Contact.FirstName, ContactRelation.Number from contact, PhoneNumber, ContactRelation where PhoneNumber.IsViberNumber = 1 and PhoneNumber.Number = ContactRelation.Number and ContactRelation.ContactID = Contact.ContactID"))
    {

        ofstream f1;
        f1.open(Pathtemp.toUtf8() + "/Viber book.txt");
        if (f1)
        {
            QSqlRecord rec2 = query2.record();
            QString    n2Number;
            QString    strName2;

            while (query2.next())
            {
                n2Number  = query2.value(rec2.indexOf("Number")).toString();
                strName2  = query2.value(rec2.indexOf("FirstName")).toString();

                if ((n2Number != "") && (strName2 != ""))
                    f1 << strName2.toStdString() << " " << n2Number.toStdString() << ";\n";
            }
        }
        f1.close();
    }

        QSqlQuery query3;
        if (query3.exec("Select Contact.FirstName, ContactRelation.Number, OriginNumberInfo.AvatarPath From OriginNumberInfo, ContactRelation, Contact Where OriginNumberInfo.Number = ContactRelation.Number and ContactRelation.ContactID = Contact.ContactID"))
        {

            ofstream f2;
            f2.open(Pathtemp.toUtf8() + "/Avatar Path.txt");
            if (f2)
            {
                QSqlRecord rec3 = query3.record();
                QString    n3Number;
                QString    strName3;
                QString    AvatarPath;

                while (query3.next())
                {
                    strName3  = query3.value(rec3.indexOf("FirstName")).toString();
                    n3Number  = query3.value(rec3.indexOf("Number")).toString();
                    AvatarPath  = query3.value(rec3.indexOf("AvatarPath")).toString();

                    if ((strName3 != "") && (n3Number != "") && (AvatarPath != ""))
                        f2 << strName3.toStdString() << " " << n3Number.toStdString() << " " << AvatarPath.toStdString() << ";\n";
                }
            }
            f2.close();
        }

            QSqlQuery query4;
            if (query4.exec("select Contact.FirstName, Events.Direction, datetime(Events.TimeStamp, 'unixepoch') from Contact, Events, ContactRelation where Events.EventID = (select Calls.EventID from Calls) AND Events.Number = ContactRelation.Number and ContactRelation.ContactID = Contact.ContactID"))
            {

                ofstream f3;
                f3.open(Pathtemp.toUtf8() + "/Calls.txt");
                if (f3)
                {
                    QSqlRecord rec4 = query4.record();
                    QString    strName4;
                    QString    Direction4;
                    QString    Time4;
                    QString    t1 = "<-";
                    QString    t0 = "->" ;

                    while (query4.next())
                    {
                        strName4  = query4.value(rec4.indexOf("FirstName")).toString();
                        Direction4  = query4.value(rec4.indexOf("Direction")).toString();
                        Time4 = query4.value(rec4.indexOf("datetime(Events.TimeStamp, 'unixepoch')")).toString();

                        if ((strName4 != "") && (Time4 != "") && (Direction4 != ""))
                        {
                            if (Direction4 == "1")
                                f3 << strName4.toStdString() << " "  << t1.toStdString() << " " << Time4.toStdString() << ";\t";
                            else
                                f3 << strName4.toStdString() << " "  << t0.toStdString() << " " << Time4.toStdString() << ";\t";
                        }
                    }
                }
                f3.close();
            }

                QSqlQuery query5, query6;
                if (query5.exec("Select ChatInfo.ChatID, Contact.FirstName, ChatInfo.Token From ChatInfo, ContactRelation, Contact where ChatInfo.Token = ContactRelation.Number and ContactRelation.ContactID = Contact.ContactID"))
                {
                    QSqlRecord rec5 = query5.record();
                    QSqlRecord rec6 = query6.record();

                    ofstream f4;

                    QString ChatID5;
                    QString FirstName5;
                    QString Token5;

                    QString    Messages6;
                    QString    strName6;
                    QString    Direction6;
                    QString    Time6;
                    QString    Path6;
                    QString    t11 = "<-";
                    QString    t00 = "->" ;

                    while (query5.next())
                    {
                        ChatID5  = query5.value(rec5.indexOf("ChatID")).toString();
                        FirstName5  = query5.value(rec5.indexOf("FirstName")).toString();
                        Token5  = query5.value(rec5.indexOf("Token")).toString();

                        if (query6.exec("select Messages.Body, Contact.FirstName, Events.Direction, Messages.ThumbnailPath, datetime(Events.TimeStamp, 'unixepoch') from messages, Events, Contact, ContactRelation where Messages.EventID = Events.EventID and Events.Number = ContactRelation.Number and ContactRelation.ContactID = Contact.ContactID and Events.ChatID = " + ChatID5 + ";"))
                        {
                            rec6 = query6.record();

                            if (FirstName5 != "")
                                f4.open(Pathtemp.toUtf8() + "/" + FirstName5.toUtf8() + " messages.txt");
                            else
                                f4.open(Pathtemp.toUtf8() + "/" + Token5.toUtf8() + " messages.txt");
                            if (f4)
                            {

                                while (query6.next())
                                {
                                    Messages6  = query6.value(rec6.indexOf("Body")).toString();
                                    strName6  = query6.value(rec6.indexOf("FirstName")).toString();
                                    Direction6  = query6.value(rec6.indexOf("Direction")).toString();
                                    Time6 = query6.value(rec6.indexOf("datetime(Events.TimeStamp, 'unixepoch')")).toString();
                                    Path6 = query6.value(rec6.indexOf("ThumbnailPath")).toString();

                                    if (Path6 == "")
                                    {
                                        if (Direction6 == "1")
                                            f4 << strName6.toStdString() << " " << t11.toStdString() << " " << Messages6.toStdString() << " " << Time6.toStdString() << ";\n";
                                        else
                                            f4 << strName6.toStdString() << " " << t00.toStdString() << " " << Messages6.toStdString() << " " << Time6.toStdString() << ";\n";
                                    }
                                    else
                                    {
                                        if (Direction6 == "1")
                                            f4 << strName6.toStdString() << " " << t11.toStdString() << " " << Messages6.toStdString() << " " << Path6.toStdString() << " " << Time6.toStdString() << ";\n";
                                        else
                                            f4 << strName6.toStdString() << " " << t00.toStdString() << " " << Messages6.toStdString() << " " << Path6.toStdString() << " " << Time6.toStdString() << ";\n";
                                    }
                                }
                            }
                        }

                    f4.close();
                    Messages6 = "";
                    strName6 = "";
                    Direction6 = "";
                    Time6 = "";
                    Path6 = "";
                }
         }
    }
}


void Win_7_8_10(QString input, QString out)
{
    int per, i, schetchik, k, m, j;
    QString FullPath, buff, Avatars, Thumbnails;

    QDir dirU(input + "/Users");
    dirU.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
    dirU.setSorting(QDir::Name);
    QFileInfoList Uslist = dirU.entryInfoList();
    QString Users[Uslist.size()];
    for (per = 0; per < Uslist.size(); per++)
    {
        QFileInfo fileInfo = Uslist.at(per);
        Users[per] = input + "/Users/" + fileInfo.fileName();
    }

    for (i = 0; i < Uslist.size(); i++)
    {
        if ((Users[i] != input + "/Users/All Users") && (Users[i] != input + "/Users/Default User") && (Users[i] != input + "/Users/Public") && (Users[i] != input + "/Users/Все пользователи"))
        {
            QDir dirUAR(Users[i] + "/AppData/Roaming");
            dirUAR.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dirUAR.setSorting(QDir::Name);
            QFileInfoList Brlist = dirUAR.entryInfoList();
            QString buffRoaming[Brlist.size()];
            schetchik = 0;
            for (per = 0; per < Brlist.size(); per++)
            {
                QFileInfo fileInfo = Brlist.at(per);
                buffRoaming[per] = Users[i] + "/AppData/Roaming/" + fileInfo.fileName();
                schetchik++;
            }

            for (k = 0; k < schetchik; k++)
            {
                if (buffRoaming[k] == Users[i] + "/AppData/Roaming/ViberPC")
                {

                    QDir dirVib(buffRoaming[k]);
                    dirVib.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
                    dirVib.setSorting(QDir::Name);
                    QFileInfoList Viblist = dirVib.entryInfoList();
                    QString Vibakk[Viblist.size()];
                    QString KatalogiViber[Viblist.size()];
                    for (m = 0; m < Viblist.size(); m++)
                    {
                        QFileInfo fileInfo = Viblist.at(m);
                        Vibakk[m] = buffRoaming[k] + "/" + fileInfo.fileName();
                        KatalogiViber[m] = fileInfo.fileName();
                    }

                    for (j = 0; j < m; j++)
                    {
                        buff = "";
                        buff = KatalogiViber[j];
                        if ((buff[0] == '7') &&(buff[1] == '9'))
                        {
                            Avatars = Vibakk[j] + "/Avatars";
                            Thumbnails = Vibakk[j] + "/Thumbnails";
                            FullPath = Vibakk[j] + "/" + "viber.db";
                            Viber_XP_7_8_10(FullPath, KatalogiViber[j], out);
                            Viber_Avatars(Avatars, KatalogiViber[j], out);
                            Viber_Thumbnails(Thumbnails, KatalogiViber[j], out);
                        }
                    }
                }
            }
        }
    }

}


void WinXP(QString input, QString out)
{
    int per, i, schetchik, k, m, j;
    QString FullPath, buff, Avatars, Thumbnails;

    QDir dirU(input + "/Documents and Settings");
    dirU.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
    dirU.setSorting(QDir::Name);
    QFileInfoList Uslist = dirU.entryInfoList();
    QString Users[Uslist.size()];
    for (per = 0; per < Uslist.size(); per++)
    {
        QFileInfo fileInfo = Uslist.at(per);
        Users[per] = input + "/Documents and Settings/" + fileInfo.fileName();
    }

    for (i = 0; i < Uslist.size(); i++)
    {
        if ((Users[i] != input + "/Documents and Settings/All Users") && (Users[i] != input + "/Documents and Settings/Default User") && (Users[i] != input + "/Documents and Settings/Public") && (Users[i] != input + "/Documents and Settings/Все пользователи"))
        {
            QDir dirUAR(Users[i] + "/Application Data");
            dirUAR.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dirUAR.setSorting(QDir::Name);
            QFileInfoList Brlist = dirUAR.entryInfoList();
            QString buffRoaming[Brlist.size()];
            schetchik = 0;
            for (per = 0; per < Brlist.size(); per++)
            {
                QFileInfo fileInfo = Brlist.at(per);
                buffRoaming[per] = Users[i] + "/Application Data/" + fileInfo.fileName();
                schetchik++;
            }

            for (k = 0; k < schetchik; k++)
            {
                if (buffRoaming[k] == Users[i] + "/Application Data/ViberPC")
                {

                    QDir dirVib(buffRoaming[k]);
                    dirVib.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
                    dirVib.setSorting(QDir::Name);
                    QFileInfoList Viblist = dirVib.entryInfoList();
                    QString Vibakk[Viblist.size()];
                    QString KatalogiViber[Viblist.size()];
                    for (m = 0; m < Viblist.size(); m++)
                    {
                        QFileInfo fileInfo = Viblist.at(m);
                        Vibakk[m] = buffRoaming[k] + "/" + fileInfo.fileName();
                        KatalogiViber[m] = fileInfo.fileName();
                    }

                    for (j = 0; j < m; j++)
                    {
                        buff = "";
                        buff = KatalogiViber[j];
                        if ((buff[0] == '7') &&(buff[1] == '9'))
                        {
                            Avatars = Vibakk[j] + "/Avatars";
                            Thumbnails = Vibakk[j] + "/Thumbnails";
                            FullPath = Vibakk[j] + "/" + "viber.db";
                            Viber_XP_7_8_10(FullPath, KatalogiViber[j], out);
                            Viber_Avatars(Avatars, KatalogiViber[j], out);
                            Viber_Thumbnails(Thumbnails, KatalogiViber[j], out);
                        }
                    }
                }
            }
        }
    }
}


bool TaskViber::execute(const coex::IConfig *config) {
    if(m_bDebug)
    {
        std::cout << "  !!! debug mode on.\n";
        std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
    }
    QString input = config->inputFolder(), output = config->outputFolder();

    if ( config->typeOS()->toString().toStdString() == "Windows XP" ) WinXP(input, output);
    else Win_7_8_10(input, output);

    return true;
};

coex::ITask* createTask() {
    return (coex::ITask*)(new TaskViber());
}
