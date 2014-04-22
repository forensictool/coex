#!/bin/bash

cd ./coex/obj
qmake-qt4 && make

../bin/coex
