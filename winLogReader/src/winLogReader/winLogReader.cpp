#include "winLogReader.h"

winLogReader::winLogReader(QString fileName, QString outFileName)
{
    m_file = new QFile(fileName);
    m_bOpen = m_file->open(QIODevice::ReadOnly);
    m_outFile = new QFile(outFileName);
    m_bOutOpen = m_outFile->open(QIODevice::Append);
}

winLogReader::~winLogReader()
{
    if (m_bOpen) m_file->close();
    if (m_bOutOpen) m_outFile->close();
}

void winLogReader::read()
{
    if(!m_bOpen)
    {
        std::cout << "input file not found" << std::endl;
        return;
    }

    if(!m_bOutOpen)
    {
        std::cout << "output file not created" << std::endl;
        return;
    }

    QDataStream inStream(m_file);
    QTextStream outStream(m_outFile);

    while(!inStream.atEnd())
    {
        QChar val;
        inStream >> val;
        outStream << val.toLatin1();
        outStream << "\n";
    }
}
