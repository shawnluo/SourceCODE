#! /bin/bash
declare -i i=0
declare -i sum=0

until ((i>10))
do
	let sum+=i
	let ++i
done
echo $sum