#include "coex.h"

#include "example_task.h"
#include "task_search_pidgin_win.h"

namespace coex {
  void initTasks(const coex::typeOS &os, QVector<coex::task*> &tasks)
  {
    coex::createTask<exampleTask>(os, tasks);
    coex::createTask<taskSearchPidginWin>(os, tasks);    
  };  

  coex::typeOS detectOS(QString /*inputFolder*/)
  {
    // TODO: detect system
    // inputFolder
    return coex::ceWindowsXP;  
  };  
};
