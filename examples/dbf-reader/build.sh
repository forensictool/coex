#!/bin/bash

# cp ../../bin/libs/libqdbf* /usr/lib/i386-linux-gnu/
rm main.o
rm dbf-reader
qmake dbf-reader.pro
make

echo "***** libraries"
ldd dbf-reader

echo "***** run app"
./dbf-reader fox_samp.dbf
./dbf-reader 657182629.db
