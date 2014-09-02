# Use to tar crash out3/58, reg_*.out to save storage----#
# Should in crash dir------------------------------------#

ls |egrep '^[0-9]+_[0-9]'>templist
totnum=`wc -l templist|cut -d' ' -f1`
for ((i=1;i<=$totnum;i=i+1))
do
    nowname=`head -$i templist|tail -1`
    if [ -e $nowname ];then
	cd $nowname
	echo $nowname
	for j in OUT3 OUT58 reg_body.out reg_single.out ks_term.out
	do
	    if [ -e $j ] ;then
#		echo $j
		tar czvf $j.tar.gz $j
		rm -f $j
	    fi
	done
	cd ..
    fi
done
