#ifndef __COEX_H__
#define __COEX_H__

#include <QString>
#include <QVector>
#include "task.h"

namespace coex {

  void initTasks(const coex::typeOS &os, QVector<coex::task*> &tasks);
  coex::typeOS detectOS(QString inputFolder);
};

#endif // __COEX_H__
