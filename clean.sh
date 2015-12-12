#!/bin/bash
OK="OK"

printf " > delete folder %-20s" "'bin'"
rm -rf 'bin'
echo $OK

printf " > delete folder %-20s" "'logs'"
rm -rf 'logs'
echo $OK

cd sources

printf " > delete all %-23s" "'Makefile'"
find . -iname 'Makefile' -delete
echo $OK

printf " > delete files %-21s" "'object'"
find . -iname '*.o' -delete
echo $OK

printf " > delete files %-21s" "'moc'"
find . -iname 'moc*.*' -delete
echo $OK

printf " > delete files %-21s" "'tmp'"
find . -iname 'tmp' -delete
echo $OK
