TEMPLATE = app
SOURCES += src/main.cpp \
  src/coex/coex.cpp \
  src/coex/coex_detectOS.cpp \
  src/coex/coex_initTasks.cpp \
  src/tasks/example_task.cpp \
  src/tasks/task_search_pidgin_win.cpp \
  src/tasks/task_search_programm_win.cpp \
  src/tasks/task_search_syslogs_lin.cpp

HEADERS += src/coex/task.h \
  src/coex/coex.h \
  src/tasks/example_task.h \
  src/tasks/task_search_pidgin_win.h \
  src/tasks/task_search_programm_win.h \
  src/tasks/task_search_syslogs_lin.h
QT += core \
 xml \
 script \
 gui \
 xmlpatterns
