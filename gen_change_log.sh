#!/bin/bash
papackage_name="coex"
version=$(git describe --long)
maintainer="$(git config user.name)"
echo "|----------------------------------------------------------------------------------------|"
echo "$  papackage_name ($version) ; urgency=low" 
git tag -l | sort -u -r | while read TAG ; do
    echo
    if [ $NEXT ];then
        echo [$NEXT]
    else
        echo "*[Current]"
    fi
    GIT_PAGER=cat git log --no-merges --format=" * %s" $TAG..$NEXT
    NEXT=$TAG
done
FIRST=$(git tag -l | head -1)
#echo
echo " -- $maintainer <alaghal@mail.ru> $(date -R) --"
echo "|----------------------------------------------------------------------------------------|"
#GIT_PAGER=cat git log --no-merges --format=" * %s" $FIRST
