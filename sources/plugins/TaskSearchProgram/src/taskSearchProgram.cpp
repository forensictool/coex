#include "taskSearchProgram.h"
#include "writerMessages.h"

#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QDir>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QCoreApplication>
#include <fstream>
#include <QDebug>
#include <sys/types.h>

TaskProgramSearch::TaskProgramSearch() {
    m_bDebug = true;
};

QString TaskProgramSearch::help() {
	return "\t--debug - viewing debug messages";
};

QString TaskProgramSearch::name() {
    return "Search Program";//
};

QString TaskProgramSearch::author() {
    return "Kucher Maxim";//
};

QString TaskProgramSearch::description() {
    return "example task";//
};

bool TaskProgramSearch::isSupportOS(const coex::ITypeOperationSystem *os) {
    return (os->platform() == "Windows" && (os->version() == "XP" || os->version() == "7" || os->version() == "8"));
};

void TaskProgramSearch::setOption(QStringList options) {
	/*
	 * 
	 * */
	if(options.contains("--debug"))
		m_bDebug = true;
};

void WinXP(QString input, QString out)
{
    writerSearchProgram ara(out + "/katalogi.xml");
    writerSearchProgram brb(out + "/install_katalogi.xml");
    int i, j, k, m, flag = 0, per;
 /*   QFile file (out + "/katalogi.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    QFile file1 (out + "/install_katalogi.txt");
    file1.open(QIODevice::WriteOnly);
    QTextStream stream1(&file1);*/
    QString ProgramFilesXP[] = { input + "/Program Files/Common Files", input + "/Program Files/ComPlus Applications", input + "/Program Files/Internet Explorer", input + "/Program Files/Messenger", input + "/Program Files/Online Services", input + "/Program Files/Outlook Express", input + "/Program Files/Windows NT", input + "/Program Files/Common Files", input + "/Program Files/ComPlus Applications", input + "/Program Files/Internet Explorer", input + "/Program Files/Messenger", input + "/Program Files/microsoft frontpage", input + "/Program Files/Movie Maker", input + "/Program Files/MSN Gaming Zone", input + "/Program Files/NetMeeting", input + "/Program Files/Online Services", input + "/Program Files/Outlook Express", input + "/Program Files/Uninstall Information", input + "/Program Files/Windows Media Player", input + "/Program Files/Windows NT", input + "/Program Files/WindowsUpdate", input + "/Program Files/xerox" };
    QString CommonFilesXP[] = { input + "/Program Files/Common Files/Microsoft Shared", input + "/Program Files/Common Files/microsoft shared", input + "/Program Files/Common Files/ODBC", input + "/Program Files/Common Files/Services", input + "/Program Files/Common Files/SpeechEngines", input + "/Program Files/Common Files/System", input + "/Program Files/Common Files/Microsoft Shared", input + "/Program Files/Common Files/MSSoap", input + "/Program Files/Common Files/ODBC", input + "/Program Files/Common Files/Services", input + "/Program Files/Common Files/SpeechEngines", input + "/Program Files/Common Files/System" };
    QString ProgramFiles86XP[] = { input + "/Program Files (x86)/Common Files", input + "/Program Files (x86)/Internet Explorer", input + "/Program Files (x86)/microsoft shared", input + "/Program Files (x86)/Movie Maker", input + "/Program Files (x86)/MSN", input + "/Program Files (x86)/MSN Gaming Zone", input + "/Program Files (x86)/NetMeeting", input + "/Program Files (x86)/Outlook Express", input + "/Program Files (x86)/speechengines", input + "/Program Files (x86)/system", input + "/Program Files (x86)/Uninstall Information", input + "/Program Files (x86)/Windows Media Player", input + "/Program Files (x86)/Windows Media Player[Strings]", input + "/Program Files (x86)/Windows NT"};
    QString CommonFiles86XP[] = { input + "/Program Files (x86)/Common Files/Microsoft Shared", input + "/Program Files (x86)/Common Files/microsoft shared", input + "/Program Files (x86)/Common Files/ODBC", input + "/Program Files (x86)/Common Files/Services", input + "/Program Files (x86)/Common Files/SpeechEngines", input + "/Program Files (x86)/Common Files/System" };
    QString ApplicationData[] = { "/Identities", "/Microsoft" };
    QString LocalSettings[] = { "/Microsoft" };
        QDir dir(input + "/");
        dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
        dir.setSorting(QDir::Name);
        QFileInfoList Clist = dir.entryInfoList();
        QString c[Clist.size()];
        for (per = 0; per < Clist.size(); per++)
        {
            QFileInfo fileInfo = Clist.at(per);
            c[per] = input + "/" + fileInfo.fileName();
        }
    for (i = 0; i < Clist.size(); i++)
    {
        if (c[i] == input + "/Program Files")
        {
            QDir dirPF(input + "/Program Files");
            dirPF.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dirPF.setSorting(QDir::Name);
            QFileInfoList Prlist = dirPF.entryInfoList();
            QString ProgramFiles[Prlist.size()];
            QString ProgramFilesName[Prlist.size()];
            for (per = 0; per < Prlist.size(); per++)
            {
                QFileInfo fileInfo = Prlist.at(per);
                ProgramFiles[per] = input + "/Program Files/" + fileInfo.fileName();
                ProgramFilesName[per] = fileInfo.fileName();
            }

            for (j = 0; j < Prlist.size(); j++)
            {
               /* stream << ProgramFiles[j] << "\n";*/
                ara.writeProgram(ProgramFiles[j], ProgramFilesName[j]);
                flag = 0;
                for (m = 0; m < sizeof(ProgramFilesXP)/sizeof(ProgramFilesXP[0]); m++)
                {
                    if (ProgramFiles[j] == ProgramFilesXP[m])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag != 1)
                {
                /*    stream1 << ProgramFiles[j] << "\n";*/
                    brb.writeProgram(ProgramFiles[j], ProgramFilesName[j]);
                }
            }
         /*   stream << "\n";
            stream1 << "\n";*/

            QDir dirC(input + "/Program Files/Common Files");
            dirC.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dirC.setSorting(QDir::Name);
            QFileInfoList Colist = dirC.entryInfoList();
            QString CommonFiles[Colist.size()];
            QString CommonFilesName[Colist.size()];
            for (per = 0; per < Colist.size(); per++)
            {
                QFileInfo fileInfo = Colist.at(per);
                CommonFiles[per] = input + "/Program Files/Common Files/" + fileInfo.fileName();
                CommonFilesName[per] = fileInfo.fileName();
            }

            for (j = 0; j < Colist.size(); j++)
            {
              /*  stream << CommonFiles[j] << "\n";*/
                ara.writeProgram(CommonFiles[j], CommonFilesName[j]);
                flag = 0;
                for (m = 0; m < sizeof(CommonFilesXP)/sizeof(CommonFilesXP[0]); m++)
                {
                    if (CommonFiles[j] == CommonFilesXP[m])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag != 1)
                {
               /*     stream1 << CommonFiles[j] << "\n";*/
                    brb.writeProgram(CommonFiles[j], CommonFilesName[j]);
                }
            }
         /*   stream << "\n";
            stream1 << "\n";*/
        }
        if (c[i] == input + "/Program Files (x86)")
        {
            QDir dirPF86(input + "/Program Files (x86)");
            dirPF86.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dirPF86.setSorting(QDir::Name);
            QFileInfoList Pr86list = dirPF86.entryInfoList();
            QString ProgramFilesx86[Pr86list.size()];
            QString ProgramFilesx86Name[Pr86list.size()];
            for (per = 0; per < Pr86list.size(); per++)
            {
                QFileInfo fileInfo = Pr86list.at(per);
                ProgramFilesx86[per] = input + "/Program Files (x86)/" + fileInfo.fileName();
                ProgramFilesx86Name[per] = fileInfo.fileName();
            }

            for (j = 0; j < Pr86list.size(); j++)
            {
         /*       stream << ProgramFilesx86[j] << "\n";*/
                ara.writeProgram(ProgramFilesx86[j], ProgramFilesx86Name[j]);
                flag = 0;
                for (m = 0; m < sizeof(ProgramFiles86XP)/sizeof(ProgramFiles86XP[0]); m++)
                {
                    if (ProgramFilesx86[j] == ProgramFiles86XP[m])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag != 1)
                {
               /*     stream1 << ProgramFilesx86[j] << "\n";*/
                    brb.writeProgram(ProgramFilesx86[j], ProgramFilesx86Name[j]);
                }
            }
       /*     stream << "\n";
            stream1 << "\n";*/

            QDir dirC86(input + "/Program Files (x86)/Common Files");
            dirC86.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dirC86.setSorting(QDir::Name);
            QFileInfoList Co86list = dirC86.entryInfoList();
            QString CommonFilesx86[Co86list.size()];
            QString CommonFilesx86Name[Co86list.size()];
            for (per = 0; per < Co86list.size(); per++)
            {
                QFileInfo fileInfo = Co86list.at(per);
                CommonFilesx86[per] = input + "/Program Files (x86)/Common Files/" + fileInfo.fileName();
                CommonFilesx86Name[per] = fileInfo.fileName();
            }

            for (j = 0; j < Co86list.size(); j++)
            {
              /*  stream << CommonFilesx86[j] << "\n";*/
                ara.writeProgram(CommonFilesx86[j], CommonFilesx86Name[j]);
                flag = 0;
                for (m = 0; m < sizeof(CommonFiles86XP)/sizeof(CommonFiles86XP[0]); m++)
                {
                    if (CommonFilesx86[j] == CommonFiles86XP[m])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag != 1)
                {
                /*    stream1 << CommonFilesx86[j] << "\n";*/
                    brb.writeProgram(CommonFilesx86[j], CommonFilesx86Name[j]);
                }
            }
         /*   stream << "\n";
            stream1 << "\n";*/
        }
        if (c[i] == input + "/Documents and Settings")
        {
            QDir dirD(input + "/Documents and Settings");
            dirD.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dirD.setSorting(QDir::Name);
            QFileInfoList Dlist = dirD.entryInfoList();
            QString Documents[Dlist.size()];
            for (per = 0; per < Dlist.size(); per++)
            {
                QFileInfo fileInfo = Dlist.at(per);
                Documents[per] = input + "/Documents and Settings/" + fileInfo.fileName();
            }

            for (j = 0; j < Dlist.size(); j++)
            {
                if ((Documents[j] != input + "/Documents and Settings/LocalService") && (Documents[j] != input + "/Documents and Settings/NetworkService"))
                {
                    QDir dirDA(Documents[j] + "/Application Data");
                    dirDA.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
                    dirDA.setSorting(QDir::Name);
                    QFileInfoList Blist = dirDA.entryInfoList();
                    QString buff[Blist.size()];
                    QString buffName[Blist.size()];
                    for (per = 0; per < Blist.size(); per++)
                    {
                        QFileInfo fileInfo = Blist.at(per);
                        buff[per] = Documents[j] + "/Application Data/" + fileInfo.fileName();
                        buffName[per] = fileInfo.fileName();
                    }

                    for (k = 0; k < Blist.size(); k++)
                    {
                   /*     stream << buff[k] << "\n";*/
                        ara.writeProgram(buff[k], buffName[k]);
                        flag = 0;
                        for (m = 0; m < sizeof(ApplicationData)/sizeof(ApplicationData[0]); m++)
                        {
                            if (buff[k] == (Documents[j] + "/Application Data" + ApplicationData[m]))
                            {
                                flag = 1;
                                break;
                            }
                        }
                        if (flag != 1)
                        {
                    /*        stream1 << buff[k] << "\n";*/
                            brb.writeProgram(buff[k], buffName[k]);
                        }
                    }
              /*      stream << "\n";
                    stream1 << "\n";*/

                    if (Documents[j] != input + "/Documents and Settings/All Users")
                    {
                        QDir dirDLA(Documents[j] + "/Local Settings/Application Data");
                        dirDLA.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
                        dirDLA.setSorting(QDir::Name);
                        QFileInfoList B1list = dirDLA.entryInfoList();
                        QString buff1[B1list.size()];
                        QString buff1Name[B1list.size()];
                        for (per = 0; per < B1list.size(); per++)
                        {
                            QFileInfo fileInfo = B1list.at(per);
                            buff1[per] = Documents[j] + "/Local Settings/Application Data/" + fileInfo.fileName();
                            buff1Name[per] = fileInfo.fileName();
                        }

                        for (k = 0; k < B1list.size(); k++)
                        {
                       /*     stream << buff1[k] << "\n";*/
                            ara.writeProgram(buff1[k], buff1Name[k]);
                            flag = 0;
                            for (m = 0; m < sizeof(LocalSettings)/sizeof(LocalSettings[0]); m++)
                            {
                                if (buff1[k] == (Documents[j] + "/Local Settings/Application Data" + LocalSettings[m]))
                                {
                                    flag = 1;
                                    break;
                                }
                            }
                            if (flag != 1)
                            {
                         /*       stream1 << buff1[k] << "\n";*/
                                brb.writeProgram(buff1[k], buff1Name[k]);
                            }
                        }
                   /*     stream << "\n";
                        stream1 << "\n";*/
                    }
                }
            }
        }
    }
  /*  file.close();
    file1.close();*/
}
void Win_7_8(QString input, QString out)
{
    writerSearchProgram ara(out + "/katalogi.xml");
    writerSearchProgram brb(out + "/install_katalogi.xml");
    int i, j, m, flag = 0, per;
/*    QFile file (out + "/katalogi.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    QFile file1 (out + "/install_katalogi.txt");
    file1.open(QIODevice::WriteOnly);
    QTextStream stream1(&file1);*/
    QString ProgramFiles78[] = { input + "/Program Files/Common Files", input + "/Program Files/DVD Maker", input + "/Program Files/Embedded Lockdown Manager", input + "/Program Files/Internet Explorer", input + "/Program Files/Microsoft.NET", input + "/Program Files/Microsoft Games", input + "/Program Files/MSBuild", input + "/Program Files/Reference Assemblies", input + "/Program Files/Uninstall Information", input + "/Program Files/Windows Defender", input + "/Program Files/Windows Journal", input + "/Program Files/Windows Mail", input + "/Program Files/Windows Media Player", input + "/Program Files/Windows Multimedia Platform", input + "/Program Files/Windows NT", input + "/Program Files/Windows Photo Viewer", input + "/Program Files/Windows Portable Devices", input + "/Program Files/Windows Sidebar", input + "/Program Files/WindowsApps", input + "/Program Files/WindowsPowerShell"};
    QString CommonFiles78[] = { input + "/Program Files/Common Files/microsoft shared", input + "/Program Files/Common Files/Microsoft Shared", input + "/Program Files/Common Files/Services", input + "/Program Files/Common Files/System", input + "/Program Files/Common Files/SpeechEngines"};
    QString ProgramFiles78x32[] = { input + "/Program Files (x86)/Common Files", input + "/Program Files (x86)/Internet Explorer", input + "/Program Files (x86)/Microsoft.NET", input + "/Program Files (x86)/MSBuild", input + "/Program Files (x86)/Reference Assemblies", input + "/Program Files (x86)/Uninstall Information", input + "/Program Files (x86)/Windows Defender", input + "/Program Files (x86)/Windows Mail", input + "/Program Files (x86)/Windows Media Player", input + "/Program Files (x86)/Windows Multimedia Platform", input + "/Program Files (x86)/Windows NT", input + "/Program Files (x86)/Windows Photo Viewer", input + "/Program Files (x86)/Windows Portable Devices", input + "/Program Files (x86)/Windows Sidebar", input + "/Program Files (x86)/WindowsPowerShell"};
    QString CommonFiles78x32[] = { input + "/Program Files (x86)/Common Files/Microsoft Shared", input + "/Program Files (x86)/Common Files/microsoft shared", input + "/Program Files (x86)/Common Files/SpeechEngines", input + "/Program Files (x86)/Common Files/Services", input + "/Program Files (x86)/Common Files/System"};
    QString ProgramData78[] = { input + "/ProgramData/Application Data", input + "/ProgramData/Desktop", input + "/ProgramData/Documents", input + "/ProgramData/Favorites", input + "/ProgramData/Microsoft", input + "/ProgramData/regid.1991-06.com.microsoft", input + "/ProgramData/Start Menu", input + "/ProgramData/Templates", input + "/ProgramData/главное меню", input + "/ProgramData/Главное меню", input + "/ProgramData/Документы", input + "/ProgramData/Избранное", input + "/ProgramData/Рабочий стол", input + "/ProgramData/Шаблоны"};
    QString Local78[] = { "/Application Data", "/EmieBrowserModeList", "/EmieSiteList", "/EmieUserList", "/History", "/Microsoft", "/Packages", "/Temp", "/Temporary Internet Files", "/VirtualStore", "/Application Data", "/History", "/Microsoft", "/Temp", "/Temporary Internet Files"};
    QString Roaming78[] = { "/Microsoft", "/Media Center Programs", "/Adobe", "/Identities", "/Microsoft", "/Media Center Programs", "/Identities"};
    QDir dir(input + "/");
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
    dir.setSorting(QDir::Name);
    QFileInfoList Clist = dir.entryInfoList();
    QString c[Clist.size()];
    for (per = 0; per < Clist.size(); per++)
    {
        QFileInfo fileInfo = Clist.at(per);
        c[per] = input + "/" + fileInfo.fileName();
    }

    for (i = 0; i < Clist.size(); i++)
    {
        if (c[i] == input + "/Program Files")
        {
            QDir dirPF(input + "/Program Files");
            dirPF.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dirPF.setSorting(QDir::Name);
            QFileInfoList Prlist = dirPF.entryInfoList();
            QString ProgramFiles[Prlist.size()];
            QString ProgramFilesName[Prlist.size()];
            for (per = 0; per < Prlist.size(); per++)
            {
                QFileInfo fileInfo = Prlist.at(per);
                ProgramFiles[per] = input + "/Program Files/" + fileInfo.fileName();
                ProgramFilesName[per] = fileInfo.fileName();
            }

            for (j = 0; j < Prlist.size(); j++)
            {
                ara.writeProgram(ProgramFiles[j], ProgramFilesName[j]);
              /*  stream << ProgramFiles[j] << "\n";*/
                flag = 0;
                for (m = 0; m < sizeof(ProgramFiles78)/sizeof(ProgramFiles78[0]); m++)
                {
                    if (ProgramFiles[j] == ProgramFiles78[m])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag != 1)
                {
                 /*   stream1 << ProgramFiles[j] << "\n";*/
                    brb.writeProgram(ProgramFiles[j], ProgramFilesName[j]);
                }
            }
       /*     stream << "\n";
            stream1 << "\n";*/

            QDir dirC(input + "/Program Files/Common Files");
            dirC.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dirC.setSorting(QDir::Name);
            QFileInfoList Colist = dirC.entryInfoList();
            QString CommonFiles[Colist.size()];
            QString CommonFilesName[Colist.size()];
            for (per = 0; per < Colist.size(); per++)
            {
                QFileInfo fileInfo = Colist.at(per);
                CommonFiles[per] = input + "/Program Files/Common Files/" + fileInfo.fileName();
                CommonFilesName[per] = fileInfo.fileName();
            }

            for (j = 0; j < Colist.size(); j++)
            {
            /*    stream << CommonFiles[j] << "\n";*/
                ara.writeProgram(CommonFiles[j], CommonFilesName[j]);
                flag = 0;
                for (m = 0; m < sizeof(CommonFiles78)/sizeof(CommonFiles78[0]); m++)
                {
                    if (CommonFiles[j] == CommonFiles78[m])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag != 1)
                {
            /*        stream1 << CommonFiles[j] << "\n";*/
                    brb.writeProgram(CommonFiles[j], CommonFilesName[j]);
                }
            }
         /*   stream << "\n";
            stream1 << "\n";*/
        }
        if (c[i] == input + "/Program Files (x86)")
        {
            QDir dirPF86(input + "/Program Files (x86)");
            dirPF86.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dirPF86.setSorting(QDir::Name);
            QFileInfoList Pr86list = dirPF86.entryInfoList();
            QString ProgramFilesx86[Pr86list.size()];
            QString ProgramFilesx86Name[Pr86list.size()];
            for (per = 0; per < Pr86list.size(); per++)
            {
                QFileInfo fileInfo = Pr86list.at(per);
                ProgramFilesx86[per] = input + "/Program Files (x86)/" + fileInfo.fileName();
                ProgramFilesx86Name[per] = fileInfo.fileName();
            }

            for (j = 0; j < Pr86list.size(); j++)
            {
             /*   stream << ProgramFilesx86[j] << "\n";*/
                ara.writeProgram(ProgramFilesx86[j], ProgramFilesx86Name[j]);
                flag = 0;
                for (m = 0; m < sizeof(ProgramFiles78x32)/sizeof(ProgramFiles78x32[0]); m++)
                {
                    if (ProgramFilesx86[j] == ProgramFiles78x32[m])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag != 1)
                {
                /*    stream1 << ProgramFilesx86[j] << "\n";*/
                    brb.writeProgram(ProgramFilesx86[j], ProgramFilesx86Name[j]);
                }
            }
         /*   stream << "\n";
            stream1 << "\n";*/

            QDir dirC86(input + "/Program Files (x86)/Common Files");
            dirC86.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dirC86.setSorting(QDir::Name);
            QFileInfoList Co86list = dirC86.entryInfoList();
            QString CommonFilesx86[Co86list.size()];
            QString CommonFilesx86Name[Co86list.size()];
            for (per = 0; per <Co86list.size(); per++)
            {
                QFileInfo fileInfo = Co86list.at(per);
                CommonFilesx86[per] = input + "/Program Files (x86)/Common Files/" + fileInfo.fileName();
                CommonFilesx86Name[per] = fileInfo.fileName();
            }

            for (j = 0; j < Co86list.size(); j++)
            {
             /*   stream << CommonFilesx86[j] << "\n";*/
                ara.writeProgram(CommonFilesx86[j], CommonFilesx86Name[j]);
                flag = 0;
                for (m = 0; m < sizeof(CommonFiles78x32)/sizeof(CommonFiles78x32[0]); m++)
                {
                    if (CommonFilesx86[j] == CommonFiles78x32[m])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag != 1)
                {
              /*      stream1 << CommonFilesx86[j] << "\n";*/
                    brb.writeProgram(CommonFilesx86[j], CommonFilesx86Name[j]);
                }
            }
       /*     stream << "\n";
            stream1 << "\n";*/
        }
        if (c[i] == input + "/ProgramData")
        {
            QDir dirPD(input + "/ProgramData");
            dirPD.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dirPD.setSorting(QDir::Name);
            QFileInfoList Prolist = dirPD.entryInfoList();
            QString ProgramData[Prolist.size()];
            QString ProgramDataName[Prolist.size()];
            for (per = 0; per < Prolist.size(); per++)
            {
                QFileInfo fileInfo = Prolist.at(per);
                ProgramData[per] = input + "/ProgramData/" + fileInfo.fileName();
                ProgramDataName[per] = fileInfo.fileName();
            }

            for (j = 0; j < Prolist.size(); j++)
            {
             /*   stream << ProgramData[j] << "\n";*/
                ara.writeProgram(ProgramData[j], ProgramDataName[j]);
                flag = 0;
                for (m = 0; m < sizeof(ProgramData78)/sizeof(ProgramData78[0]); m++)
                {
                    if (ProgramData[j] == ProgramData78[m])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag != 1)
                {
               /*     stream1 << ProgramData[j] << "\n";*/
                    brb.writeProgram(ProgramData[j], ProgramDataName[j]);
                }
            }
        /*    stream << "\n";
            stream1 << "\n";*/
        }
    }

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

            QDir dir(Users[i] + "/AppData/Local");
            dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dir.setSorting(QDir::Name);
            QFileInfoList Blist = dir.entryInfoList();
            QString buffLocal[Blist.size()];
            QString buffLocalName[Blist.size()];
            for (per = 0; per < Blist.size(); per++)
            {
                QFileInfo fileInfo = Blist.at(per);
                buffLocal[per] = Users[i] + "/AppData/Local/" + fileInfo.fileName();
                buffLocalName[per] = fileInfo.fileName();
            }

            for (j=0; j < Blist.size(); j++)
            {
             /*   stream << buffLocal[j] << "\n";*/
                ara.writeProgram(buffLocal[j], buffLocalName[j]);
                flag = 0;
                for (m = 0; m < sizeof(Local78)/sizeof(Local78[0]); m++)
                {
                    if (buffLocal[j] == (Users[i] + "/AppData/Local" + Local78[m]))
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag != 1)
                {
                /*    stream1 << buffLocal[j] << "\n";*/
                    brb.writeProgram(buffLocal[j], buffLocalName[j]);
                }
            }
        /*    stream << "\n";
            stream1 << "\n";*/

            QDir dirUAR(Users[i] + "/AppData/Roaming");
            dirUAR.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden );
            dirUAR.setSorting(QDir::Name);
            QFileInfoList Brlist = dirUAR.entryInfoList();
            QString buffRoaming[Brlist.size()];
            QString buffRoamingName[Brlist.size()];
            for (per = 0; per < Brlist.size(); per++)
            {
                QFileInfo fileInfo = Brlist.at(per);
                buffRoaming[per] = Users[i] + "/AppData/Roaming/" + fileInfo.fileName();
                buffRoamingName[per] = fileInfo.fileName();
            }

            for (j = 0; j < Brlist.size(); j++)
            {
           /*     stream << buffRoaming[j] << "\n";*/
                ara.writeProgram(buffRoaming[j], buffRoamingName[j]);
                flag = 0;
                for (m = 0; m < sizeof(Roaming78)/sizeof(Roaming78[0]); m++)
                {
                    if (buffRoaming[j] == (Users[i] + "/AppData/Roaming" + Roaming78[m]))
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag != 1)
                {
                /*    stream1 << buffRoaming[j] << "\n";*/
                    brb.writeProgram(buffRoaming[j], buffRoamingName[j]);
                }
            }
       /*     stream << "\n";
            stream1 << "\n";*/
        }
    }
/*    file.close();
    file1.close();*/
}


bool TaskProgramSearch::execute(const coex::IConfig *config) {
	if(m_bDebug) {
		std::cout << "  !!! debug mode on.\n";
        std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
	};
    QString input = config->inputFolder(), output = config->outputFolder();
    int m = 0;
    std::cout << "OC XP? Yes - 1; No - 2\n";
    std::cin >> m;
    if ( m == 1 ) WinXP(input, output);
    else Win_7_8(input, output);

	return true;
};

coex::ITask* createTask() {
    return (coex::ITask*)(new TaskProgramSearch());
}
