#!/usr/bin/bash



exec 1>$1 #направляем поток вывода в файл с заданным названием

if [ -d $2 ] #если каталог существует
then
	cd $2
	for file in *
	do
	ext=${file##*.}
	if [ "$ext" == "$3" ]
	then
	echo $file
	fi
	done
fi
