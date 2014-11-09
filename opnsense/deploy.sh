#!/bin/sh

OIFS=$IFS
IFS="
"
                
for filename in `cat install.list|grep -v "^#" | grep "/usr/ports"  `;
do
	SRC=`echo $filename | awk '{print $1;}'`
	TARGET=`echo $filename | awk '{print $2;}'`

	echo -n "  > deploy $SRC ..."
	rm -rf $TARGET >/dev/null 2>&1
	mkdir -p $TARGET
	cp -R $SRC/* $TARGET/
	echo "done"
	
done

IFS=$OIFS
