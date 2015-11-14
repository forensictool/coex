#!/bin/bash

./build.sh

if [ -d debian ] ; then
	rm -r debian/
fi

rm *.deb

papackage_name="coex"
echo "Script for creatting .deb package for $papackage_name"  
mkdir -p debian/DEBIAN
mkdir -p debian/usr/bin
cp bin/coex ./debian/usr/bin
mkdir -p debian/usr/share/doc/$papackage_name
mkdir -p debian/usr/share/man

touch debian/usr/share/doc/$papackage_name/copyrigth
touch debian/usr/share/man/

./gen_change_log.sh > debian/DEBIAN/changelog

cat bin/LICENSE > debian/DEBIAN/copyrigth
cat bin/README >> debian/DEBIAN/copyrigth

version=$(git describe --long)
platform="all"
echo "Package: $papackage_name" > debian/DEBIAN/control
echo "Version: $version" >> debian/DEBIAN/control
echo "Section: admin" >> debian/DEBIAN/control
echo "Priority: optional" >> debian/DEBIAN/control
echo "Architecture: $platform" >> debian/DEBIAN/control
echo "Depends: g++ (>= 4.8.4)" >> debian/DEBIAN/control
echo "Maintainer: Andrey Seryakov" >> debian/DEBIAN/control
echo "Description: Project KIBEVS-1401: Computer forensics" >> debian/DEBIAN/control

name="$papackage_name""_""$version""_""$platform.deb"
echo $name
dpkg-deb --build ./debian

mv debian.deb $name



