#include "coex.h"

#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QIODevice>

namespace coex {
  coex::typeOS detectOS(QString inputFolder)
  {
    QFileInfo fi(inputFolder + "//Windows//System32//kernel32.dll");

    if(fi.exists())
    {
      QFile file(fi.fullPath());
      if (file.open(QIODevice::ReadOnly)) 
      {
        QByteArray fileData = file.readAll();
        QByteArray hashData = QCryptographicHash::hash(fileData, QCryptographicHash::Md5);
        QString str = hashData.toHex();

        if(str == "941b22338052e8a0ada7944b827e3e2a") // 6.2.9200.16627
         return coex::ceWindows8;
    };

    return coex::ceWindowsXP;  
  };  
};
