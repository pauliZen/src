#Used for tran out3 to root------------------------------#
# Need used in the root directory------------------------#
savedir='~/data/rootdata'

if [ -e $savedir ];then
    echo $savedir' exist'
else
    mkdir $savedir
fi

ls |egrep '^[13570]+_[0-9]'>templist
totnum=`wc -l templist|cut -d' ' -f1`
for ((i=1;i<=$totnum;i=i+1))
do
    nowdir=`head -$i templist|tail -1`
    nstar=`echo $nowdir|cut -d'_' -f1`
    nplanet=`echo $nowdir|cut -d'_' -f4`
    nplanet=`calc \*n $nstar $nplanet`
    nbin=`echo $nowdir|cut -d'_' -f3`
    nbin=`calc \*n $nstar $nbin`
    if [ -e $nowdir ]; then
	cd $nowdir
	if [ -e OUT3 ] && [ -e OUT58 ]; then
	    echo $nowdir' '$nstar' '$nplanet' '$nbin
	    trans_ou3 1 $nowdir 0 $savedir/ $nstar $nplanet $nbin ./
	    if [[ -e out3_finish ]] && [[ -e $savedir/$nowdir'_out3_0.root' ]]; then
		rm -f OUT3 OUT58
	    else
		echo $nowdir >>unsuclist_out3
	    fi
	else
	    echo 'No OUT3 or OUT58 found in '$nowdir
	fi
	cd ..
    else
	echo 'No '$nowdir' found'
    fi
done

    