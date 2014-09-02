function lssh()
{
    line=`egrep dragon$1 ~/.ssh/dragon.list`
    ihost=`echo $line|cut -d':' -f2`
    yname=`whoami`
    ssh -Y $yname@$ihost
}

function lscp()
{
    iname=0
    idown=0
    sfile=""
    tfile=""
    idir=0
    until [[ `echo $1` == '' ]]
    do
	case $1 in
	    -h) shift; iname=$1; shift;;
	    -d) idown=1; shift;;
	    -r) idir=1; shift;;
	    *) sfile=$sfile' '$tfile; tfile=$1; shift;;
	esac
    done
    line=`egrep dragon$iname ~/.ssh/dragon.list`
    ihost=`echo $line|cut -d':' -f2`
    yname=`whoami`
    hostn=$yname@$ihost
    if [ $idown -eq 1 ]; then
	sfilepath=""
	for i in $sfile
	do
	    sfilepath=$sfilepath' '$hostn:$i
	done
	if [ $idir -eq 1 ]; then
	    scp -r $sfilepath $tfile
	else
	    scp $sfilepath $tfile
	fi
    else
	if [ $idir -eq 1 ]; then
	    scp -r $sfile $hostn:$tfile
	else
	    scp $sfile $hostn:$tfile
	fi
    fi
}
