# mv end run dir to ../
# should used in crash directory
function crashcheck() 
{
    cd $1
    if [ -e run.log ]; then
	if [ `tail -1 run.log|egrep -c 'END RUN'` = 1 ];then	    
	    cd ..
	    mv $1 ../
	    echo 'mv '$1
	    cnum=`calc + $cnum 1`
	else
	    cd ..
	fi
    else
	cd ..
    fi
}

ls |egrep [0-9]+_[0-9]+ >nowlist
totnum=`wc -l nowlist|cut -d' ' -f1`
cnum=0
for ((i=1;i<=$totnum;i=i+1))
do
    if [ -e nowlist ]; then
	nowdir=`head -$i nowlist|tail -1`
	crashcheck $nowdir
    else
	echo 'Error: '$nowdir
	break
    fi
done

echo 'check finished, find '$cnum
rm nowlist
ls >../crashlist
