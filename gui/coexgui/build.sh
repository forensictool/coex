#!/bin/bash
CURRPWD=$(echo "`pwd`")
cd ../../ && ./build.sh
cp -R bin/coex bin/plugins $CURRPWD
