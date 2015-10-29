#include "taskOutlook.h"
#include "writerAddress.h"

taskOutlook::taskOutlook() {
    m_bDebug = false;
};

QString taskOutlook::help() {
    return "\t--debug - viewing debug messages";
};

QString taskOutlook::name() {
    return "Outlook";
};

QString taskOutlook::author() {
    return "Serakov Andrey";
};

QString taskOutlook::description() {
    return "TaskOutlook2007 task";
};

bool taskOutlook::isSupportOS(const coex::ITypeOperationSystem *os) {
    return (os->platform() == "Windows");
};

void taskOutlook::setOption(QStringList options) {

    if(options.contains("--debug"))
        m_bDebug = true;
};

QStringList Prov(QStringList list,QStringList oflist)
{
    for(int i=0; i<list.length(); i++)
    {
        QString ter;
        int k;
        k=ter.length();
        ter=list[i];
        if (    ter.at(0)==QChar('\r') &&
                ter.at(1)==QChar('\n')&&
                ter.at(2)==QChar('\t')&&
                ter.at(3)==QChar('S') &&
                ter.at(4)==QChar('a'))
        {
            ter = ter.remove(0,8);
            ter = ter.remove(k-2,2);
            oflist<<ter;

        }
        if (ter.at(0)==QChar('<'))
        {

            ter = ter.remove(0,1);
            ter = ter.remove(k-1,1);
            oflist<<ter;
        }
        if (    ter.at(0)==QChar(' ') &&
                ter.at(1)==QChar('u')&&
                ter.at(2)==QChar('n')&&
                ter.at(3)==QChar('d') &&
                ter.at(4)==QChar('e'))
        {

            ter = ter.remove(0,13);
            ter = ter.remove(k-2,2);
            oflist<<ter;

        }


        if (ter.at(0)==QChar('\r') &&
                ter.at(1)==QChar('\n')&&
                ter.at(2)==QChar('S')&&
                ter.at(3)==QChar('u') &&
                ter.at(4)==QChar('b'))
        {

            ter = ter.remove(0,10);
            ter = ter.remove(k-2,2);
            oflist<<ter;

        }

        if (ter.at(0)==QChar('\r') &&
                ter.at(1)==QChar('\n')&&
                ter.at(2)==QChar('T')&&
                ter.at(3)==QChar('o') &&
                ter.at(4)==QChar(':'))
        {

            ter = ter.remove(0,5);
            ter = ter.remove(k-2,2);
            oflist<<ter;

        }

    }


    return oflist;
};

bool taskOutlook::execute(const coex::IConfig *config) {
    if(m_bDebug) {
        std::cout << "  !!! debug mode on.\n";
        std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
    };

    QDir dirOut(config->outputFolder());
    dirOut.mkdir("Outlook");
    QFile file;
    QString value;
    QStringList listTheme,listAddressOtp,listText,listToAddress,ListDate;
    QStringList oflistTheme,oflistAddressOtp,oflistText,oflistToAddress,ofListDate;
    qint32 stapseek;
    qint32 smesh;
    qint32 endfile;
    endfile= file.size();
    smesh=120;
    stapseek=246529;
    std::cout << "\n";
    QRegExp pathAccount(".*.dbx");
    QDirIterator dirPath(config->inputFolder(), QDir::Files | QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
    while (dirPath.hasNext()) {
        if (dirPath.filePath().contains(pathAccount))
        {
           QString filepath= dirPath.fileName();
           QFile filepathe(filepath);
           if( filepathe.open( QFile::ReadOnly ) )
            {
                while(stapseek<endfile)
                {
                    if( file.seek(stapseek) )
                    {
                        value = file.read(smesh);
                        qDebug() << value; // never gets here
                        QString reg="(\r\nSubject: \\w+\r\n)";
                        QString reg1="( undefined\r\n\r\n\\w+\r\n)";
                        QString reg2="(<\\w+@\\w+.\\w+>)";
                        QString reg3="(\r\nTo: \\w+@\\w+.\\w+\r\n)";
                        QString reg4="(\r\n\t\\w+, \\S+ \\S+ \\S+ \\S+ \\S+\r\n)";
                        QRegExp rx(reg);
                        QRegExp rx1(reg1);
                        QRegExp rx2(reg2);
                        QRegExp rx3(reg3);
                        QRegExp rx4(reg4);
                        int pos = 0;
                        while ((pos = rx.indexIn(value, pos)) != -1)
                        {
                            listTheme <<rx.cap(1);
                            pos += rx.matchedLength();
                        }
                        int pos1 = 0;
                        while ((pos1 = rx1.indexIn(value, pos1)) != -1)
                        {
                            listText <<rx1.cap(1);
                            pos1 += rx1.matchedLength();
                        }
                        int pos2 = 0;
                        while ((pos2 = rx2.indexIn(value, pos2)) != -1)
                        {
                            listAddressOtp <<rx2.cap(1);
                            pos2 += rx2.matchedLength();
                        }
                        int pos3 = 0;
                        while ((pos3 = rx3.indexIn(value, pos3)) != -1)
                        {
                            listToAddress <<rx3.cap(1);
                            pos3 += rx3.matchedLength();
                        }
                        int pos4 = 0;
                        while ((pos4 = rx4.indexIn(value, pos4)) != -1)
                        {
                            ListDate <<rx4.cap(1);
                            pos4 += rx4.matchedLength();
                        }
                        stapseek+=smesh;
                    }
                }

                oflistAddressOtp = Prov(listAddressOtp,oflistAddressOtp);
                oflistText=Prov(listText,oflistText);
                oflistTheme=Prov(listTheme,oflistTheme);
                oflistToAddress=Prov(listToAddress,oflistToAddress);
                ofListDate=Prov(ListDate,ofListDate);
                file.close();
            }
            else
            {
                qDebug()<<"No opene";
            }

            dirPath.next();
        }
    };
    for (int i=0; i< oflistAddressOtp.length(); i++)
    {
        writerAddressOutlook OutlookMessage(config->outputFolder()+"//Outlook/Message.xml",oflistAddressOtp[i]);
        //OutlookMessage.writerAddressOutlook;
        OutlookMessage.writeMessage(oflistAddressOtp[i],ofListDate[i],oflistText[i],oflistTheme[i]);
    }

    return true;
}

coex::ITask* createTask()
{
    return (coex::ITask*)(new taskOutlook());
}
