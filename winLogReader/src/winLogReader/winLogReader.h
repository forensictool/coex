#ifndef WIN_LOG_READER_H
#define WIN_LOG_READER_H

#include <iostream>
#include <QString>
#include <QFile>

class winLogReader
{
    public:
        winLogReader(QString fileName, QString outFileName);
        ~winLogReader();

    private:
        QFile *m_file;
        QFile *m_outFile;
        bool m_bOpen;
        bool m_bOutFile;
};

#endif
