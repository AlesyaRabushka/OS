#!/usr/bin/bash

if [ -f $1 ]
then
	gcc $1 -o $2
		if [ $? -ne 0 ]
		then
		echo "Coulld not execute program" 
		else
		./$2
		fi
else
	echo "Файл $1 не найден"
fi




