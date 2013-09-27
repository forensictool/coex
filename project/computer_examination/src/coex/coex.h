#ifndef __COEX_H__
#define __COEX_H__

#include <QString>
#include <QVector>
#include "task.h"

namespace coex {

  void initTasks(const coex::typeOS &os, QVector<coex::task*> &tasks);
  coex::typeOS detectOS(QString inputFolder);
  QString typeOStoString(const coex::typeOS &os);
  void printConfig(const coex::config& cnf);
  bool writeConfig(const coex::config& cnf);
};

#endif // __COEX_H__
