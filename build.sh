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

echo " * * build plugins"
cd $SOURCES/plugins
for D in `find ./ -mindepth 1 -maxdepth 1 -type d `
do
	cd $SOURCES/plugins
	cd $D
	DIRNAME=$(basename "`pwd`")
	echo -ne " * build '$DIRNAME'"

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

echo " * * build libs"
cd $SOURCES/libs
for D in `find ./ -mindepth 1 -maxdepth 1 -type d `
do
	cd $SOURCES/libs
	cd $D
	DIRNAME=$(basename "`pwd`")
	echo -ne " * build '$DIRNAME'"

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

# create version file

cd $CURRPWD/bin


echo "The MIT License (MIT)
 
Copyright (c) 2013-2014 GPO-1011-Forensics
 
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the \"Software\"), to deal in
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of 
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions: 
The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software. 
THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS 
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
" > LICENSE

echo "
Thanks for using our software.

Product: coex
Version: 0.2.`git rev-list HEAD --count`
Date: `date`
Address: Russia, Tomsk, st. Lenina, 40
Organization: TUSUR
Author: GPO-1011-Forensics

Developers:
Alexey Gulyaev (kondorbrn@gmail.com),
Evgenii Sopov (sea-kg@ya.ru),
Dmitrii Nikiforov (nds@keva.tusur.ru),
Alinka Morgunenko (??),
Igor Polyakov (??)
Oleg Rachkovan  (??)
Vladislav Shipovskoi (??)
Marina Meyta (somekindofcookiemonster@gmail.com)
Oleg Lobanov (??)
Serakov Andrey (??)

Using third party:
QDbf: arial79@gmail.com, https://code.google.com/p/qdbf/

" > README

