#!/usr/bin/bash

file_search(){
	for file in *
	do
		if [ -d $file ]
		then
			cd $file
			file_search
		else
			stat -c "%s %A %n" $file
		fi
	done
}


file_search

