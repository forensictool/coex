#include "coex.h"

#include "../tasks/example_task.h"
#include "../tasks/task_search_pidgin_win.h"
#include "../tasks/task_search_pidgin_unix.h"
#include "../tasks/task_search_skype_win.h"
#include "../tasks/task_imprintFromProgramFiles_win.h"
#include "../tasks/task_search_syslogs_lin.h"
#include "../tasks/task_search_syslogs_win.h"

namespace coex {
  void initTasks(const coex::typeOS &os, QVector<coex::task*> &tasks, bool bNeedAll)
  {
    coex::createTask<exampleTask>(os, tasks, bNeedAll);
    coex::createTask<taskSearchSkypeWin>(os, tasks, bNeedAll);
    coex::createTask<taskSearchPidginWin>(os, tasks, bNeedAll);
    coex::createTask<taskSearchPidginUnix>(os, tasks, bNeedAll);
    coex::createTask<taskSearchProgrammWin>(os, tasks, bNeedAll);
    coex::createTask<taskSearchSyslogsLin>(os, tasks, bNeedAll);
    coex::createTask<taskSearchSyslogsWin>(os, tasks, bNeedAll);
  };
};
