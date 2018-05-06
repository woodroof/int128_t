#!/bin/bash
if [ $# == 1 ]
then
	filename=${1/\.cpp/}
	clang++ -Wl,-no_pie -O3 --std=c++14 -I ~/src/boost/boost -I ~/src/sltbench/install/include/ -I .. -L ~/src/sltbench/install/lib -lsltbench $1 -o $filename
else
	for i in *.cpp
	do
		filename=${i/\.cpp/}
		clang++ -Wl,-no_pie -O3 --std=c++14 -I ~/src/boost/boost -I ~/src/sltbench/install/include/ -I .. -L ~/src/sltbench/install/lib -lsltbench $i -o $filename
	done
fi
