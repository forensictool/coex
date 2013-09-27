#include "coex.h"

#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QIODevice>
#include <QList>

namespace coex {

/*
  struct fileos
  {
     fileos(QString filePath, QString hash, QString version, coex::typeOS os) :
      filePath(filePath), hash(hash), version(version), os(os) 
     {
     };
     QString filePath;
     QString hash;
     QString version;
     coex::typeOS os;

     QString toString() {
       return "filePath: " + filePath + "; hash: " + hash + "; version: " + version + "; os: " + typeOStoString(os) + ";";
     };
  };
*/

  coex::typeOS detectOS(QString inputFolder)
  {
  /*
    QList<fileos> listfiles;
    QList<fileos> checkfiles;

    listfiles << fileos(
      "//WINDOWS//system32//kernel32.dll", 
      "d612ee36f95da6d1179f7567b2b77d77",
      "5.1.2600.5512",
      coex::ceWindowsXP
    );

    listfiles << fileos(
      "//Windows//System32//kernel32.dll", 
      "5b4b379ad10deda4eda01b8c6961b193",
      "6.1.7600.16385",
      coex::ceWindows7
    );

    listfiles << fileos(
      "//Windows//System32//kernel32.dll", 
      "941b22338052e8a0ada7944b827e3e2a",
      "6.2.9200.16627",
      coex::ceWindows8
    );

    for(int i = 0; i < listfiles.size(); i++)
    {
       QFileInfo fi(inputFolder + listfiles[i].filePath);
       if(fi.exists())
       {
         QFile file(fi.fullPath());
         if (file.open(QIODevice::ReadOnly)) 
         {
           QByteArray fileData = file.readAll();
           QByteArray hashData = QCryptographicHash::hash(fileData, QCryptographicHash::Md5);
           QString str = hashData.toHex();
                      
           if(str.toLowerCase() == listfiles[i].hash.toLowerCase())
             checkfiles << listfiles[i];
         }
       }
    }

    if(checkfiles.size() == 0)
      return coex::ceUnknown;


    coex::typeOS os_result = coex::ceUnknown;
    // check on conflicts
    {
      int nCounter = 0;
      for(int x = 0; x < checkfiles.size()-1; x++)
      for(int y = x+1; y < checkfiles.size(); y++)
      {
        if(checkfiles[x].os != checkfiles[y].os)
        {
           std::cout << " conflict between: \n\t " 
              << checkfiles[x].toString().toStdString() 
              << "\n\t and " << checkfiles[y].toString().toStdString() << "\n";
           nCounter++;
        };
      };
      if(nCounter == 0) 
        os_result = checkfiles[0].os;
    };

    return os_result;
    */
    return coex::ceWindowsXP;
  };  
};
