
pid=`ps -u $PsUser|grep $PsName|grep -v grep|grep -v vi|grep -v dbx |grep -v tail|grep -v start|grep -v stop |sed -n 1p |awk '{print $1}'`
pid=`ps -u $PsUser|grep $PsName|grep -v grep|grep -v vi|grep -v dbx |grep -v tail|grep -v start|grep -v stop |sed -n 1p |awk '{print $1}'`
echo $pid 
