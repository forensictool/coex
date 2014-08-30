#!/bin/bash
CURRPWD=$(echo "`pwd`")
SOURCES=$(echo "`pwd`/sources")
OK=" ..... ok"

LOGFILE="$CURRPWD/logs/log_build.log"
ERRORLOGFILE="$CURRPWD/logs/errorlog_build.log"

if [ ! -d "logs" ]; then
  mkdir "logs"
fi

echo $SOURCES > $LOGFILE

echo -ne " * build 'coex'"
cd $SOURCES/app/
qmake-qt4
make >> $LOGFILE 2>> $ERRORLOGFILE
echo $OK

echo " * build plugins"
cd $SOURCES/plugins
for D in `find ./ -mindepth 1 -maxdepth 1 -type d `
do
	cd $SOURCES/plugins
	cd $D
	DIRNAME=$(basename "`pwd`")
	echo -ne " * * build '$DIRNAME'"

	qmake-qt4 >> $LOGFILE 2>> $ERRORLOGFILE
	if [ $? -ne 0 ]; then
		echo ""
		echo "ERRORS, log look in file: $ERRORLOGFILE"
		exit;
	fi

	make >> $LOGFILE 2>> $ERRORLOGFILE
	if [ $? -ne 0 ]; then
		echo ""
		echo "ERRORS, log look in file: $ERRORLOGFILE"
		exit;
	fi
	echo $OK
done

