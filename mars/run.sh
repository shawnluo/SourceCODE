#!/bin/bash
#set -x
#make clean
#make && clear;

echo $@

#VAR=""

for VAR in "$@"
do
    args+=$VAR
    args+=" "
    #echo -n "$VAR "
done

#echo $args
./build/mars $args