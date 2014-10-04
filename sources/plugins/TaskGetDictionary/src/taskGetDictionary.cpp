#include "taskGetDictionary.h"

#include "coexDb.h"

#include <iostream>
#include <QDirIterator>
#include <QString>
#include <QRegExp>
#include <QFile>
#include <QFileInfo>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QDir>
#include <qtextcodec.h>

TaskGetDictionary::TaskGetDictionary() {
  m_bDebug = false;
};

QString TaskGetDictionary::help() {
  return "\t--debug - viewing debug messages";
};

QString TaskGetDictionary::name() {
  return "getDictionary";
};

QString TaskGetDictionary::author() {
  return "unknown";
};

QString TaskGetDictionary::description() {
  return "getDictionary task";
};

bool TaskGetDictionary::isSupportOS(const coex::ITypeOperationSystem *os) {
  return (os->platform() == "Windows");
};

void TaskGetDictionary::setOption(QStringList options) {
  /*
   * 
   * */
  if(options.contains("--debug"))
    m_bDebug = true;
};

bool TaskGetDictionary::execute(const coex::IConfig *config) 
{
  if(m_bDebug) 
  {
    std::cout << "  !!! debug mode on.\n";
    std::cout << "InputFolder: " << config->inputFolder().toStdString() << "\n";
  };

  QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale()); 
  QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
  std::cout << "---------------------------------------------------------" << std::endl;
  QString dirStr(config->inputFolder());
  QString outDirStr(config->outputFolder());
  outDirStr.append("/dictionary");
  QDir().mkdir(outDirStr);
  
  CoexDB db(outDirStr + "/db.db");

  /*outDirStr.append("/dictionary.txt");
  QFile outFile(outDirStr);
  if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text)&&(m_bDebug))
  {
    std::cout << "ERROR: can't open output file" << std::endl;
  }
  QTextStream out(&outFile);*/
  QDirIterator fileListDirit(dirStr, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
  QStringList buf;
  while(fileListDirit.hasNext())
  {
    QString str = QString("%1").arg(fileListDirit.next());
    QFileInfo fInfo(str);
    //QRegExp reWord("([а-яА-Яa-zA-Z0-9])+");
    //int pos = 0;
    if(fInfo.suffix() == "txt")
    {
      //std::cout << fInfo.absoluteFilePath().toStdString() << std::endl;
      QFile file(fInfo.absoluteFilePath());
      if(file.open(QIODevice::ReadOnly | QIODevice::Text))
      {
        while(!file.atEnd())
        {
          str = file.readLine();
          QStringList list = str.split(QRegExp("\\W+"), QString::SkipEmptyParts);
          for(int i = 0; i < list.count(); i++)
          {
            /*str = list.at(i);
            if(buf.indexOf(str) == -1)
            {
              buf.append(str);
            }*/
            db.insert(list.at(i));
          }
        }
        file.close();
      }
    }
  }
  /*buf.sort();
  for(int i = 0; i < buf.count(); i++)
  {
    out << buf.at(i) << "\n";
  }
  outFile.close();*/
  std::cout << "---------------------------------------------------------" << std::endl;
  return true;
};

coex::ITask* createTask() 
{
  return (coex::ITask*)(new TaskGetDictionary());
}
