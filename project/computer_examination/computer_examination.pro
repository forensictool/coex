TEMPLATE = app
SOURCES += src/main.cpp \
  src/coex/coex.cpp \
  src/coex/writerMessages.cpp \
  src/coex/coex_detectOS.cpp \
  src/coex/coex_initTasks.cpp \
  src/tasks/example_task.cpp \
  src/tasks/task_search_skype_win.cpp \
  src/tasks/task_search_pidgin_win.cpp \
  src/tasks/task_search_pidgin_unix.cpp \
  src/tasks/task_imprintFromProgramFiles_win.cpp \
  src/tasks/task_search_syslogs_lin.cpp \
  src/tasks/task_search_syslogs_win.cpp \
  src/winEventReader/evtReader.cpp

HEADERS += src/coex/task.h \
  src/coex/coex.h \
  src/coex/writerMessages.h \
  src/tasks/example_task.h \
  src/tasks/task_search_skype_win.h \
  src/tasks/task_search_pidgin_win.h \
  src/tasks/task_search_pidgin_unix.h \
  src/tasks/task_imprintFromProgramFiles_win.h \
  src/tasks/task_search_syslogs_lin.h \
  src/tasks/task_search_syslogs_win.h \
  src/winEventReader/evtReader.h


QT += core \
 xml \
 script \
 gui \
 xmlpatterns
