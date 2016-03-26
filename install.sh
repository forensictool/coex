#!/bin/bash
echo "Install coex"
cd //
cd etc/apt
sudo su -c "echo 'deb http://rep.coex.su linux non-free' >> sources.list"
gpg --keyserver keyserver.ubuntu.com --recv F442F58696D6E45E
sudo su -c "gpg --export --armor F442F58696D6E45E" | sudo su -c "apt-key add --"
if[["$OSTYPE" -eq "Debian"]]
	then	
		sudo su -c "aptitude update"
		sudo su -c "aptitude install coex"
		exit 1
	elif [["$OSTYPE" -eq "Linux" ]]
		then
			sudo su -c "apt-get update"
			sudo su -c "apt-get install coex"	
fi