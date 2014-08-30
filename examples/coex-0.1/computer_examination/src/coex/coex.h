#ifndef __COEX_H__
#define __COEX_H__

#include <QString>
#include <QVector>
#include <QStringList>
#include <QMap>
#include "task.h"
#include "writerMessages.h"

namespace coex {

  void initTasks(const coex::typeOS &os, QVector<coex::task*> &tasks, bool bNeedAll = false);
  coex::typeOS detectOS(QString inputFolder);
  QString typeOStoString(const coex::typeOS &os);
  void printConfig(const coex::config& cnf);
  bool writeConfig(const coex::config& cnf);
  void parseArguments(int argc, const char* argv[], QStringList &list, QMap<QString, QStringList> &options);
  void printManual(const QString &nameProgram, QVector<coex::task*> &man_tasks);
};

#endif // __COEX_H__
