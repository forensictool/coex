#ifndef HDD_H
#define HDD_H

#include <QList>
#include <QFileInfo>
#include <QStringList>
#include <QDir>

class Hdd
{
    private:
        QList<QDir> infoList;

    public:
        Hdd(QList<QDir> list);
        ~Hdd();
        QFileInfoList getFiles(QStringList wildcardlist);
        QFileInfoList getFiles(QString wildcard);
};

#endif // HDD_H
