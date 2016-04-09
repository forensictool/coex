#!/bin/bash
papackage_name="coex"
versionNewDeb=$(git describe --long)
#Eqvile old and new verssion *.deb package
valueOldContainVersionDeb = $(cat fileContainVersionCoex)
if [["$valueOldContainVersionDeb" -eq "$versionNewDeb"]]
	then
	 	echo "Version new package dont matches with old version package"
else 
	echo "$version" > fileContainVersionCoex
	./creat_package.sh 
	echo "Deb package full update"
fi