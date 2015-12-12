#!/bin/bash

./build.sh

if [ -d debian ] ; then
	rm -r debian/
fi

rm *.deb

papackage_name="coex"
version=$(git describe --long)
echo "Script for creatting .deb package for $papackage_name"  
mkdir -p debian/DEBIAN
mkdir -p debian/usr/bin
cp bin/coex ./debian/usr/bin

##Image for coex
mkdir -p debian/usr/share/doc/$papackage_name
mkdir -p debian/usr/share/man
mkdir -p debian/usr/share/applications
mkdir -p debian/usr/share/icons/hicolor/64x64/apps
cp  avatar-63.jpg ./debian/usr/share/icons/hicolor/64x64/apps

##Plugins and libs for COEX Binary 
mkdir -p debian/usr/coex/plugins
mkdir -p debian/usr/coex/libs
cp -R bin/plugins/ ./debian/usr/coex/plugins
cp -R bin/libs/ ./debian/usr/coex/libs

## Dock and Manual
touch debian/usr/share/doc/$papackage_name/copyrigth
touch debian/usr/share/man/ 

##Create file HistoryOfChange for Committing changes in deb package 
./gen_change_log.sh >> HistoryOfChange

## The changelog file
# Как написать условие проверки на повторяющиеся изменения???
cat HistoryOfChange > debian/usr/share/doc/$papackage_name/changelog.Debian

## The copyrigth file
cat bin/LICENSE > debian/usr/share/doc/$papackage_name/copyrigth

## The file README
cat bin/README  > debian/usr/share/doc/$papackage_name/README

## The control file
platform="all"
maintainer="$(git config user.name)"
echo "Package: $papackage_name" > debian/DEBIAN/control
echo "Version: $version" >> debian/DEBIAN/control
echo "Section: admin" >> debian/DEBIAN/control
echo "Priority: optional" >> debian/DEBIAN/control
echo "Architecture: $platform" >> debian/DEBIAN/control
echo "Depends: g++ (>= 4.8.4), libqt4-opengl (>= 4:4.7.2), libqtcore4 (>= 4:4.8.0),libqt4-xml (>= 4:4.5.3),libgtk2.0-0 (>= 2.24.0),libqtgui4 (>= 4:4.6.1)" >> debian/DEBIAN/control
echo "Maintainer: $maintainer" >> debian/DEBIAN/control
echo "Description: Project KIBEVS-1401: Computer forensics" >> debian/DEBIAN/control

## The Applications 
echo "Name=$papackage_name">debian/usr/share/applications/coex.desktop
echo "Comment=$papackage_name for forensics">>debian/usr/share/applications/coex.desktop
echo "GenericName= tool of forensics">>debian/usr/share/applications/coex.desktop
echo "Exec=$papackage_name">>debian/usr/share/applications/coex.desktop
echo "Icon=$papackage_name">>debian/usr/share/applications/coex.desktop
echo "Categories=tool for forensics">>debian/usr/share/applications/coex.desktop
echo "Terminal=true">>debian/usr/share/applications/coex.desktop
echo "Type=Application">>debian/usr/share/applications/coex.desktop
echo "Version=$version">>debian/usr/share/applications/coex.desktop

## The md5sums file (DEBIAN/md5sums)
# !! It works incorrectly
#find . -type f ! -regex '.*.hg.*' ! -regex '.*?debian-binary.*' ! -regex '.*?DEBIAN.*' -printf '%P ' | xargs md5sum > debian/DEBIAN/md5sums
md5deep -r debian/usr > debian/DEBIAN/md5sums

## The package assembly
name="$papackage_name""_""$version""_""$platform.deb"
echo $name
fakeroot dpkg-deb --build ./debian

mv debian.deb $name