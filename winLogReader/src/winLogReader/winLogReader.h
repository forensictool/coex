#ifndef WIN_LOG_READER_H
#define WIN_LOG_READER_H

#include <iostream>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDataStream>

class winLogReader
{
    public:
        winLogReader(QString fileName, QString outFileName);
        ~winLogReader();
        virtual void read();

    private:
        QFile *m_file;
        QFile *m_outFile;
        bool m_bOpen;
        bool m_bOutOpen;
};

#endif
