#include "hdd.h"

Hdd::Hdd(QString path){
    QDirIterator dirPath(path, QDir::Files |QDir::Dirs| QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
    QList<QDir> dirlist;
    dirlist->append(QDir(path));

    while (dirPath.hasNext())
    {
        dirlist->append(QDir(dirPath.next()));
    }

    this->infoList = dirlist;
}

Hdd::~Hdd(){

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
