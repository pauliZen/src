#Draw dEvsT,EvsT,Lout/in,Ldist,Lcum by drawdEgraph-------#
#Need drawlist.lst, [dirname]-result-dat.lst--------------#
#--------------------------------------------------------#

figdir=/home/lwang/Dropbox/Datas/BHdata/figures/
numlim=5000

if [ -e drawlist.lst ]&&[ -e calcstar.lst ];then
    num=`wc -l drawlist.lst|cut -d' ' -f1`
    for ((i=1;i<=$num;i=i+1))
    do
	name=`head -$i drawlist.lst|tail -1|cut -d' ' -f1`
	bhmass1=`head -$i drawlist.lst|tail -1|cut -d' ' -f2`
	bhmass2=`head -$i drawlist.lst|tail -1|cut -d' ' -f3`
	crit=`egrep $name'\ ' calcstar.lst|cut -d' ' -f3`
	echo $name $bhmass1 $bhmass2 $crit
	if [ -e $name'-dat.lst' ];then
	    pf=`head -1 $name'-dat.lst'`
	    pd=`tail -1 $name'-dat.lst'`
	    indexname=$name'-select-star.index'
	    if [ -e $indexname ];then
		totline=`wc -l $indexname |cut -d' ' -f1`
		if [ -d $figdir$name ]; then
		    echo 'run '$name
		else
		    mkdir $figdir$name
		fi
		if [ $totline -ge $numlim ]; then
		    echo "large index "$totline", splited index"
		    drawdEgraph $name $figdir$name'/' "selstars"  "destars" "dEvsT_all" "EvsT_all" "Lchange" "Ldist" "LcumvsT" 10 $bhmass1 $bhmass2 "E"$pf"to"$pd $crit
		else
		    echo $totline
		    drawdEgraph $name $figdir$name'/' "selstars" "destars" "dEvsT_all" "EvsT_all" "Lchange" "Ldist" "LcumvsT" 1 $bhmass1 $bhmass2 "E"$pf"to"$pd $crit
		fi
	    else
		echo 'no indexname '$indexname
	    fi
	else
	    echo 'no dat.lst '$name'-dat.lst'
	fi
    done
else
    echo 'no drawlist.lst'
fi
