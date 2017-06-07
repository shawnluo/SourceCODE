#! /bin/bash
function xxxx 
{	
	declare -i i=0
	pid=`ps -e | grep good | awk '{print $4}'`

	if [ $pid = "good" ]
	then
#		echo "good exist!"

		until (i=1)
		do
#			xx=`x get --fw_version | sed -n '5,8p' awk '{print $2}'`
			xx=`ps -ef`
			echo $xx
			if [ $xx = "2 11 1 40" ]
			then
				echo "success!"
				let i=1
			fi
		done
	fi
}

xxxx;
