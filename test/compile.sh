#!/bin/bash
if [ $# == 1 ]
then
	filename=${1/\.cpp/}
	clang++ -O3 --std=c++14 -I ~/src/boost/boost -I .. -I ~/src/thirdparty/Include -L ~/src/out/Debug -lgoogletest $1 -o $filename
else
	for i in *.cpp
	do
		filename=${i/\.cpp/}
		clang++ -O3 --std=c++14 -I ~/src/boost/boost -I .. -I ~/src/thirdparty/Include -L ~/src/out/Debug -lgoogletest $i -o $filename
	done
fi
