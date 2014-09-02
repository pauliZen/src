#Calculate dE vs time by star-delta-energy---------------------#
#Consider splited index, store data in [dirname]-result-dE.root#
#Need dirlist.lst, [dirname]-select-star.index[.**]            #
#Multi-processes, uplimit threads is 10                        #

thres=4  #uplimit threads 
filenum=10  #"index file number(should less then 10)"
numlim=5000
bhindex1=999998
bhindex2=999999

function checkjob()
{
    while [ `jobs|wc -l` -ge $thres ]
    do
	jobs -l
	echo "wait 1m"
	sleep 1m
    done
}

if [ -e dirlist.lst ];then
    num=`wc -l dirlist.lst|cut -d' ' -f1`
    for ((i=1;i<=$num;i=i+1))
    do
	rootname=`head -$i dirlist.lst|tail -1`
	nrootname=$rootname"-result-dEt"
	treename='selstars'
	ntreename='destars'
	ntreetitle="dE_vs_time_analysis_of_selstars"
	indexname=$rootname'-select-star.index'
	if [ -e $indexname ];then
	    totline=`wc -l $indexname |cut -d' ' -f1`
	    if [ $totline -ge $numlim ]; then
		echo "large index "$totline", splited index"
		for ((j=0;j<$filenum;j=j+1))
		do
		    checkjob
		    echo "now name "$rootname$j
		    star-delta-energy $rootname $nrootname"-"$j".root" $treename$j $ntreename $ntreetitle$j $indexname".0"$j $bhindex1 $bhindex2 $rootname"-dE-twice-"$j".log" $rootname"-dE-fail-"$j".log" > $rootname"-dE-"$j".log" &
		done
	    else
		checkjob
		echo "now name "$rootname
		star-delta-energy $rootname $nrootname".root" $treename $ntreename $ntreetitle $indexname $bhindex1 $bhindex2 $rootname"-dE-twice.log" $rootname"-dE-fail.log" > $rootname"-dE.log" &
	    fi
	else
	    echo 'No indexname '$indexname
	fi
    done
fi
