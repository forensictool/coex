#include "coex.h"

#include "tasks/example_task.h"
#include "tasks/task_search_pidgin_win.h"
#include "tasks/task_search_programm_win.h"

namespace coex {
  void initTasks(const coex::typeOS &os, QVector<coex::task*> &tasks)
  {
    coex::createTask<exampleTask>(os, tasks);
    coex::createTask<taskSearchPidginWin>(os, tasks);
    coex::createTask<taskSearchProgrammWin>(os, tasks);
  };  

  coex::typeOS detectOS(QString /*inputFolder*/)
  {
    // TODO: detect system
    // inputFolder
    return coex::ceWindowsXP;  
  };  
};
