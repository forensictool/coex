#!/bin/bash
OK=" ..... ok"

echo -ne " * delete folder 'bin'"
rm -rf 'bin'
echo $OK

echo -ne " * delete folder 'logs'"
rm -rf 'logs'
echo $OK

cd sources

echo -ne " * delete all 'Makefile'"
find . -iname 'Makefile' -delete
echo $OK

echo -ne " * delete all '*.o'"
find . -iname '*.o' -delete
echo $OK

echo -ne " * delete all 'moc*.*'"
find . -iname 'moc*.*' -delete
echo $OK

echo -ne " * delete all 'tmp'"
find . -iname 'tmp' -delete
echo $OK
