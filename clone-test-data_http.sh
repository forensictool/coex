#!/bin/bash

TESTDATA="tmp/test-data"
if [ ! -d "tmp" ]; then
  mkdir "tmp"
fi

echo " * clone or pull 'coex-testdata.git'";
if [ ! -d $TESTDATA ]; then
  git clone http://gitlab2.keva.su/gpo/coex-testdata.git $TESTDATA
else
  cd $TESTDATA
  git pull
  cd ..
fi
