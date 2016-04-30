#ifndef HDD_H
#define HDD_H

#include <QList>
#include <QFileInfo>
#include <QStringList>
#include <QDir>
#include <QDirIterator>

class Hdd
{
    private:
        QList<QDir> infoList;

    public:
        Hdd(QString path);
        ~Hdd();
        QFileInfoList getFiles(QStringList wildcardlist);
        QFileInfoList getFiles(QString wildcard);
};

#endif // HDD_H
