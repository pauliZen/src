ls *.ccd>changelist
for ((i=1;i<=`cat changelist|wc -l`;i=i+1))
do
    oldname=`head -$i changelist|tail -1`
    numb=`echo $oldname|cut -b 2-|cut -d'.' -f1`
    if [ `echo $numb|wc -c` -lt 3 ];then
	numb='00'$numb
    fi
    if [ `echo $numb|wc -c` -lt 4 ]; then
	numb='0'$numb
    fi
#    echo $numb
    newname=`egrep -m 1 $numb'\.fit' fitlist`
    if [ `echo $newname|wc -c` -lt 2 ]; then
	echo 'nomatch' $oldname
	mv $oldname others
    else
	echo $oldname $newname
	mv $oldname $newname
    fi

done

rm changelist
