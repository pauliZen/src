#Used for tran reg_body.out to root------------------------------#
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
	if [ -e reg_body.out ]; then
	    echo $nowdir
	    trans_body 1 $nowdir 0 $savedir/ ./
	    if [[ -e body_finish ]] && [[ -e $savedir/$nowdir'_body_0.root' ]];then
		rm -f reg_body.out
	    else
		echo $nowdir >>../unsuclist_body
	    fi
	else
	    echo 'No reg_body found in '$nowdir
	fi
	cd ..
    else
	echo 'No '$nowdir' found'
    fi
done
