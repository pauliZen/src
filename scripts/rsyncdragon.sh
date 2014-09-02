function lsync()
{
    if [ -e ~/.ssh/dragon.list ]; then
	flag=0
	tardir=bin
	delopt=""
	until [ $flag = 1 ];
	do
	    case $1 in
		-s) shift;tardir=$1;shift;;
		-del) delopt="--delete";shift;;
		*) flag=1;
	    esac
	done
	mhost=`hostname|cut -d'.' -f1`
	mname=`whoami`
	if [[ $mhost == dragon0 ]]; then
	    dlist=`cat ~/.ssh/dragon.list`
	    for i in $dlist
	    do
		iname=`echo $i|cut -d':' -f1`
		ihost=`echo $i|cut -d':' -f2`
		if [[ $iname != dragon0 ]] ; then
		    echo -e "\033[33mSend "$tardir" to "$iname"\033[0m"
		    rsync -rlvu $delopt ~/$tardir $mname@$ihost:
		fi
	    done
	else
	    echo -e "\033[33mreceive "$tardir$" from dragon0\033[0m"
	    ipdragon0=`egrep dragon0 ~/.ssh/dragon.list|cut -d':' -f2`
	    rsync -rlvu $delopt $mname@$ipdragon0:$tardir ~/
	fi
    fi
}
