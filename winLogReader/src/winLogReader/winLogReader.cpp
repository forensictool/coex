#include "winLogReader.h"

winLogReader::winLogReader(QString fileName, QString outFileName)
{
    m_file = new QFile(fileName);
    m_bOpen = m_file->open(QIODevice::ReadOnly);
    m_outFile = new QFile(outFileName);
    m_bOutFile = m_outFile->open(QIODevice::Append);
}

winLogReader::~winLogReader()
{
    if (m_bOpen) m_file->close();
    if (m_bOutFile) m_outFile->close();
}


