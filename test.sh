#!/bin/bash

# ./clone-test-data.sh

TESTDATA="tmp/test-data"
TESTS="tmp/tests"

# check folder $TESTDATA
if [ ! -d $TESTDATA ]; then
  echo "folder '$TESTDATA' - not found (script: clone-test-data)"
  exit
fi

echo " * clean '$TESTS'";
if [ ! -d $TESTS ]; then
  mkdir $TESTS;
else
  rm -rf $TESTS;
  mkdir $TESTS; 
fi


# check folder $TESTS;
if [ ! -d $TESTS ]; then
  echo "folder '$TESTS' - not found"
  exit;
fi

if [ ! -d "bin" ]; then 
  ./build.sh
fi

cd bin

for D in `find ../$TESTDATA -mindepth 1 -maxdepth 1 -type d `
do
	DIRNAME=$(basename "$D")
	if [ $DIRNAME != ".git" ]; then
		echo " test folder '$DIRNAME'"
		mkdir ../$TESTS/$DIRNAME
		# ./coex :all "$TESTDATA/WindowsXP_SP3_Pro" "WinXPSP3Pro"
		./coex ../$TESTDATA/$DIRNAME ../$TESTS/$DIRNAME
		if [ $? -ne 0 ]; then
			echo "ERROR"
			exit;
		fi
	fi
done
