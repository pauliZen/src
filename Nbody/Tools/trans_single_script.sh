#Used for tran reg_single.out to root------------------------------#
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
    if [ -e $nowdir ]; then
	cd $nowdir
	if [ -e reg_single.out ]; then
	    echo $nowdir
	    trans_single 1 $nowdir 0 $savedir/ ./
	    if [[ -e single_finish ]] && [[ -e $savedir/$nowdir'_single_0.root' ]]; then
		rm -f reg_single.out
	    else
		echo $nowdir >>unsuclist_single
	    fi
	else
	    echo 'No reg_single found in '$nowdir
	fi
	cd ..
    else
	echo 'No '$nowdir' found'
    fi
done
