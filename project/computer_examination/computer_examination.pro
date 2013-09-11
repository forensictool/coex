TEMPLATE = app
SOURCES += src/main.cpp \
  src/coex/coex.cpp \
  src/coex/tasks/example_task.cpp \
  src/coex/tasks/task_search_pidgin_win.cpp \
  src/coex/tasks/task_search_programm_win.cpp

HEADERS += src/coex/task.h \
  src/coex/coex.h \
  src/coex/tasks/example_task.h \
  src/coex/tasks/task_search_pidgin_win.h \
  src/coex/tasks/task_search_programm_win.h
QT += core \
 xml \
 script \
 gui \
 xmlpatterns
