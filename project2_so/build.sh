#!/bin/bash

find . -iname 'Makefile' -delete
find . -iname '*.o' -delete

cd apps/coex/obj
qmake-qt4 && make

cd ../../../libs/detectOS/obj
qmake-qt4 && make

cd ../../winSysLog/obj
qmake-qt4 && make

