ls |egrep ^[0-9]+_[0-9\.]+_[0-9\.]+_[0-9\.]+_[0-9]+_[0-9]+>v4list
ls |egrep ^[0-9]+_[0-9\.]+_[0-9\.]+_[0-9\.]+_[0-9]+$>v0list
thres=6  #uplimit threads 

function checkjob()
{
    while [ `jobs|wc -l` -ge $thres ]
    do
	jobs -l
	echo "wait 1m"
	sleep 1m
    done
}

for i in 0 4
do
    gli=7
    [ $i = 0 ] && gli=5
    for j in 500 1000 2000
    do
	rm -f $j'v'$i.log
	cat v$i'list' |egrep ^$j|awk '{print $1" "$1}'|sed "s/_/ /g$gli">$j'v'$i.lst
	avedata $i $j'v'$i.lst $j'v'$i.root "../root/" $j'v'$i.filelst $j'v'$i.parlst 1>>$j'v'$i.log 2>>$j'v'$i.log&
    done
done
