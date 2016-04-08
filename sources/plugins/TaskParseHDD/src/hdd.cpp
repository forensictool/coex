#include "hdd.h"

Hdd::Hdd(QList<QDir> list){

    Hdd::infoList = list;
}

QFileInfoList Hdd::getFiles(QStringList wildcardlist){

    QFileInfoList allists;
    foreach(QDir dir, Hdd::infoList){
        allists.append(dir.entryInfoList( wildcardlist, QDir::Files  | QDir::NoSymLinks | QDir::Hidden ));
    }

    return allists;
}

QFileInfoList Hdd::getFiles(QString wildcard){

    QStringList wildcardlist;
    wildcardlist.append(wildcard);
    return Hdd::getFiles(wildcardlist);
}
