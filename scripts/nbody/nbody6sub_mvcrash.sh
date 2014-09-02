# check whether it is in the crashlist
# used in main directory
function crashcheck() 
{
    if [ `egrep -c $1 crashlist` -ge 1 ]; then
	echo $1' is crash dup.'
	rm -rf $1
	cnum=`calc + $cnum 1`
    else
	cd $1
	if [ -e run.log ]; then
	    if [ `tail -1 run.log|egrep -c 'END RUN'` = 0 ];then	    
		echo $1' crash'
		echo '*** Crash  '$1>>Info.txt
		tail -1 run.log>>../Info.txt
		cd ..
		mv $1 crash/
		cnum=`calc + $cnum 1`
	    else
		cd ..
	    fi
	else
	    echo $1' crash'
	    echo '*** Crash  '$1>>Info.txt
	    echo 'no run.log file'>>../Info.txt
	    cd ..
	    mv $1 crash/
	fi
    fi
}

ls crash >crashlist
ls |egrep [0-9]+_[0-9]+ >nowlist
totnum=`wc -l nowlist|cut -d' ' -f1`
cnum=0
for ((i=1;i<=$totnum;i=i+1))
do
    nowdir=`head -$i nowlist|tail -1`
    crashcheck $nowdir
done

echo 'check finished, find '$cnum
rm nowlist
ls crash >crashlist
