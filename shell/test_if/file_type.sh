#!/bin/bash
if [ -f $1 ]
then
	echo "is file"
elif [ -d $1 ]
then
	echo "is dir"
else
	echo "special"
fi
