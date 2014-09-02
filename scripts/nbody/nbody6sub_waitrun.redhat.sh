#Check crash run and end them. --------------------------#
#Used for ending crashed nbodyrun.sh---------------------#
#redhat version------------------------------------------#

Appname=nbody6_new
SRunNum=9
Stoptime=10
sleeptime=1m
function timecompare() #In: t1, t2 (t1>t2,unit:hh:mm); Print: t1-t2
{
    hour1=`echo $1|cut -d':' -f1`
    min1=`echo $1|cut -d':' -f2`
    hour2=`echo $2|cut -d':' -f1`
    min2=`echo $2|cut -d':' -f2`
    ttime1=`calc \* $hour1 60`
    ttime1=`calc + $ttime1 $min1`
    ttime2=`calc \* $hour2 60`
    ttime2=`calc + $ttime2 $min2`
    echo `calc - $ttime1 $ttime2`
}

function waitrun() #Infile: joblist; In: Appname; Outfile: joblist, Info.txt; Out: crashnum
{
    while [ -e joblist ]
    do
	echo 'Running check'
	echo `cat joblist|wc -l`' running now'
	rm -f jobtmp
	if [ `cat joblist|wc -l` -ge 1 ]; then
	    for ((wi=1;wi<=`cat joblist|wc -l`;wi=wi+1))
	    do
		thisid=`head -$wi joblist|tail -1|cut -d':' -f1`
		thisname=`head -$wi joblist|tail -1|cut -d':' -f2`
		if [ `ps -p $thisid|wc -l` = 1 ]; then
		    echo $thisid' '$thisname' finished'
		else
		    cd $thisname
		    if [ -e run.log ]; then
			if [ `tail -1 run.log|egrep -c 'END RUN'` = 1 ];then
			    echo $thisid' '$thisname' end run'
			    cd ..
			else
			    runlogtime=`ls -l|egrep 'run.log'|sed 's/\([a-zA-Z]\+\) \(\w\+\) \([0-9]\+:[0-9]\+\)/|\1-\2-\3|/'|cut -d'|' -f2`
			    runlogday=`echo $runlogtime|cut -d'-' -f2`
			    runtottime=`echo $runlogtime|cut -d'-' -f3`
#			    runlogtime=`ls -l|egrep 'run.log$'|sed 's/\(\w\+-\w\+-\w\+\) \([0-9]\+:[0-9]\+\)/|\1-\2|/'|cut -d'|' -f2`
#			    runlogday=`echo $runlogtime|cut -d'-' -f3`
#			    runtottime=`echo $runlogtime|cut -d'-' -f4`
			    righttime=`date +%R`
			    if [ `date +%d` -ne $runlogday ]; then
				righttimeh=`date +%H`
				righttimem=`date +%M`
				righttimeh=`calc + $righttimeh 24`
				righttime=`echo $righttimeh':'$righttimem`
			    fi
			    deltat=`timecompare $righttime $runtottime`
			    echo $thisid' '$thisname' running. run response time difference: '$deltat'='$righttime'-'$runtottime
			    if [ $deltat -gt $Stoptime ]; then
				kill $thisid
				echo $thisid' '$thisname' no response, kill it'
				cd ..
				mv $thisname crash/
				crashnum=`calc + $crashnum 1`
			    else
				cd ..
				echo $thisid':'$thisname >>jobtmp
			    fi
			fi
		    else
			echo '!!!'$thisid' '$thisname'Error run, no run.log, stop'
			cd ..
			break
		    fi
		fi
	    done
	    rm -f joblist
	    if [ -e jobtmp ]; then
		cat jobtmp>joblist
		rm -f jobtmp
	    fi
	fi
	if [ -e joblist ]; then
	    if [ `cat joblist|wc -l` -ge $SRunNum ]; then
		echo '-------------now running:-------------'
		cat joblist
		echo '--------------------------------------'
		echo 'running number reach maximum, wait for 3m'
		sleep 3m
	    else
		echo '-------------now running:-------------'
		cat joblist
		echo '--------------------------------------'
		break
	    fi
	else
	    echo 'No running, continue...'
	    break
	fi
    done
}

export waitrun
export timecompare

while [ -e joblist ]
do
    waitrun
    if [ -e joblist ]; then
	sleep $sleeptime
    else
	break
    fi
done

ls |egrep -i '[0-9]+_[0-9]+_[0-9]'|sed 's/_/ /g'>nowlist
