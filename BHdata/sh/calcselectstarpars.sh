#Calculate star E&L from index by select-stars-log-------#
#Need calcstar.lst (dirname,bhsplitnum,log(-de/e)>*)-----#
#store in selstars in [dirname]-result.root--------------#
#Function: auto-split index to 10 files when index list--#
#          larger than 5000 -----------------------------#
numlim=5000
splitfn=10

if [ -e calcstar.lst ];then
    num=`wc -l calcstar.lst|cut -d' ' -f1`
    for ((i=1;i<=$num;i=i+1))
    do
	name=`head -$i calcstar.lst|tail -1|cut -d' ' -f1`
	indexname=$name'-select-star.index'
	bhsplitnum=`head -$i calcstar.lst|tail -1|cut -d' ' -f2`
	selcond=`head -$i calcstar.lst|tail -1|cut -d' ' -f3`
	echo $name' '$indexname
	if [ -e $indexname ];then
	    totline=`wc -l $indexname |cut -d' ' -f1`
	    if [ $totline -ge $numlim ]; then
		echo "large index "$totline", split to 10 files"
		splitline=`calc /n $totline $splitfn`
		splitline=`calc + $splitline 1`
		split -l $splitline $indexname -d -a 2 $indexname"."
		for ((j=0;j<$splitfn;j=j+1))
		do
		    echo "now name "$name" "$j
		    select-stars-log $name "selstars"$j "select_star_by_log(-dE/E_start)>"$selcond $indexname".0"$j $name'-dat.lst' $bhsplitnum
		done
	    else
		echo "run "$name
		select-stars-log $name "selstars" "select_star_by_log(-dE/E_start)>"$selcond $indexname $name'-dat.lst' $bhsplitnum >$name'-calc-select-star.log'&
	    fi
	else
	    echo 'No indexname '$indexname
	fi
    done
else
    echo 'No calcstar.lst'
fi
jobs -l >job.lst
