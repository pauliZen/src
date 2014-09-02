#---SSH TOOLS---------------------------------------------------------------------#
function findip()
{
    flag=0
    iforward=0
    inameline=4
    forscp=0
    sname=""
    outonlyaddress=0
    outonlyuser=0
    outport=0
    outuseraddress=0
    until [ $flag = 1 ];
    do
	case $1 in
	    -f) shift; iforward=1;;
	    -P) shift; forscp=1;;
	    -i) shift; outonlyaddress=1;;
	    -u) shift; outonlyuser=1;;
	    -iu) shift; outuseraddress=1;;
	    -p) shift; outport=1;;
	    *) sname=$1;flag=1;;
	esac
    done
    iline=`egrep ip$sname= ~/.host_list|egrep -v '^#'|head -1`
    [ `echo $iline|egrep -c '#L'` = 0 ] && iforward=0
    [ `echo $iline|egrep -c '#p'` = 0 ] || inameline=5
    if [ $iforward = 1 ]; then
	ipname=`echo $iline|cut -d'#' -f$inameline|sed 's/ //g'`
	let inameline--
	iport=`echo $iline|cut -d'#' -f$inameline|cut -d' ' -f2-10|cut -d':' -f1`
	[ $outonlyaddress = 1 ] && echo 127.0.0.1 && return
	[ $outonlyuser = 1 ] && echo $ipname && return
	[ $outuseraddress = 1 ] && echo $ipname@127.0.0.1 && return
	if [ $outport = 1 ]; then
	    if [ $forscp = 0 ]; then
		echo '-p '$iport
	    else
		echo '-P '$iport
	    fi
	elif [ $forscp = 0 ]; then
	    echo "-p "$iport" "$ipname@127.0.0.1
	else
	    echo '-P '$iport" "$ipname@127.0.0.1
	fi
    else
	ipname=`echo $iline|cut -d'#' -f2|sed 's/ //g'`
	ipdress=`echo $iline|cut -d'=' -f2|cut -d'#' -f1|sed 's/ //g'`
	[ $inameline = 5 ] && iport=`echo $iline|cut -d'#' -f3|cut -d'p' -f2`
	[ $outonlyaddress = 1 ] && echo $ipdress && return
	[ $outonlyuser = 1 ] && echo $ipname && return
	if [ $outport = 1 ]; then
	    [ $inameline = 4 ] && return
	    if [ $forscp = 0 ]; then
		echo '-p '$iport
	    else
		echo '-P '$iport
	    fi
	else
	    [[ $iline = '' ]] || echo $ipname'@'$ipdress
	fi
    fi
}

function setportf()
{
    flag=0
    ipchange=0
    killnowport=0
    iport=22
    ipname=""
    until [ $flag = 1 ]
    do
	case $1 in
	    -p) shift; iport=$1; ipchange=1;shift;;
	    -k) shift; killnowport=1;;
	    *) ipname=$1;flag=1;shift;;
	esac
    done
    [ `egrep ^ip$ipname= ~/.host_list |egrep -c '#L'` -gt 0 ] || return
    Lpox=3
    Lnamepox=4
    if [ $ipchange = 0 ] && [ `egrep ^ip$ipname= ~/.host_list|egrep -c '#p'` -gt 0 ]; then
	ipchange=1
	iport=`egrep ^ip$ipname= ~/.host_list|cut -d'#' -f3|cut -d'p' -f2`
    fi
    [ $ipchange = 1 ] && Lpox=4
    [ $ipchange = 1 ] && Lnamepox=5
    ipll=`egrep ^ip$ipname= ~/.host_list|cut -d'#' -f$Lpox|cut -d' ' -f2-10`
    myname=`whoami`
    ihost=`findip $ipname`
    ipuid=`ps ax|egrep "ssh -p $iport $ihost -f -L $ipll" |egrep -v 'egrep'|awk '{print $1}'`
    if [[ $ipuid != '' ]]; then
	if [ $killnowport = 1 ] ;then
	    kill $ipuid
	    klist=`ssh -p $iport $ihost 'ps ax'|egrep 'tail -f /etc/motd'|awk '{print $1}'`
	    [[ $klist != '' ]] && ssh -p $iport $ihost kill $klist
	    ssh -p $iport $ihost -f -L $ipll tail -f /etc/motd
	fi
    else
	ssh -p $iport $ihost -f -L $ipll tail -f /etc/motd
    fi
}

function serv()
{
    iiname=''
    ioption=''
    ikill=''
    until [[ `echo $1` == '' ]]
    do 
	case $1 in
	    -l) cat ~/.host_list|egrep '^ip';break;;
	    -h) echo 'serv [-l list all host; (optional) -k kill previous forwording] [hostname] [(optional)command]';break;;
	    -k) ikill='-k';shift;;
	    *)
		if [[ $iiname == '' ]]; then
		    iiname=$1
		else
		    ioption=$1
		fi; shift;;
	esac
    done
    [[ $iiname == '' ]] && return
    [[ `findip $iiname` = '' ]] && echo "Server "$iiname" not found." && return
    setportf $ikill $iiname
    ssh -Y `findip -p $iiname` `findip -f $iiname` $ioption
}

function ssync()
{
    syfin=0
    sydirect=0
    sydestname=0
    opt=""
    deleteopt=""
    tardir="Datas"
    rdir="Dropbox/"
    until [ $syfin = 1 ];
    do
	case $1 in
	    -h) echo 'servsync [-d(inverse direction)] [-del(--delete)] [-o rsync_option] [-s target_directory(in Dropbox -list to check)] server_name(lighter,kiaa,silk0,dragon)';break;;
	    -list) echo 'Target List: '`ls -m ~/Dropbox`;break;;
	    -d) sydirect=1;shift;;
	    -o) shift;opt=$1;shift;;
	    -del) deleteopt="--delete";shift;;
	    -s) shift;tardir=$1;rdir="Dropbox/";shift;;
	    -t) shift;tardir=$1;rdir="";shift;;
	    *) sydestname=$1;syfin=1;;
	esac
    done
    [ `egrep -c ip$sydestname= ~/.host_list` = 0 ] && echo "Server name "$sydestname" not found."&& return
    iport=`findip -p $sydestname`
    setportf $iport $sydestname
    iport=`findip -f -p $sydestname`
    if [ $sydirect = 0 ] ; then
	rsync -rlvu --rsh="ssh $iport" $deleteopt $opt ~/$rdir$tardir `findip -f -iu $sydestname`:$rdir
    else
	rsync -rlvu --rsh="ssh $iport" $deleteopt $opt `findip -f -iu $sydestname`:$rdir$tardir ~/$rdir
    fi
}

function sscp()
{
    iname=0
    idown=0
    sfile=""
    tfile=""
    option=""
    idir=0
    until [[ `echo $1` == '' ]]
    do
	case $1 in
	    -h) shift; iname=$1; shift;;
	    -d) idown=1; shift;;
	    -r) idir=1; shift;;
	    -o) shift; option=$1; shift;;
	    *) sfile=$sfile' '$tfile; tfile=$1; shift;;
	esac
    done
    hostn=`findip -f -P $iname`
    hostport=""
    if [ `echo $hostn|egrep -c "\-P"` -gt 0 ]; then
	hostn=`findip -f -P $iname|awk '{print $3}'`
	hostport=`findip -f -P $iname|awk '{print $1" "$2}'`
    fi
    [[ `echo $hostn|cut -d'@' -f2` == "127.0.0.1" ]] && setportf $iname
    if [ $idown -eq 1 ]; then
	sfilepath=""
	for i in $sfile; do sfilepath=$sfilepath' '$hostn:$i; done;
	if [ $idir -eq 1 ]; then
	    scp -r $option $hostport $sfilepath $tfile
	else
	    scp $option $hostport $sfilepath $tfile
	fi
    else
	if [ $idir -eq 1 ]; then
	    scp -r $option $hostport $sfile $hostn:$tfile
	else
	    scp $option $hostport $sfile $hostn:$tfile
	fi
    fi
}

function exposerv()
{
    [ -e ~/.host_list ] || return
    iplist=`egrep '^ip\w+=' ~/.host_list |cut -d'=' -f1`
    for i in $iplist
    do
	iserv=`echo $i|sed 's/^ip//g'`
	export $i=`findip -f -i $iserv`
	iservtmp=`findip -f -P $iserv`
	export $iserv="$iservtmp"
    done
}

exposerv

#checkserver
function chkserver()
{
    flag=0
    num=10
    sopt='-%cpu,-%mem,-uid'
    popt=aux
    cserv=""
    until [ $flag = 1 ];
    do
	case $1 in
	    -h) echo 'chkserver [-n num] [-s sort option] [-o ps option] [servername]';break;;
	    -n) shift;num=$1;shift;;
	    -s) shift;sopt=$1;shift;;
	    -o) shift;popt=$1;shift;;
	    *) cserv=$1;flag=1;;
	esac
    done
    [[ $cserv == "" ]] && return
    ihost=`findip -f $cserv`
    [[ $ihost == '@' ]] && echo 'Server not found!' && return
    echo -e "\033[43m\033[30m"$cserv"--"`date`"-------------------------------------------------\033[0m"
    num=`expr $num + 1`
    [ `egrep ip$cserv= ~/.host_list |egrep -c '#L'` = 0 ] || setportf $cserv
    ssh `findip -f $cserv` "ps $popt --sort=$sopt|egrep -v 'ps '$popt' --sort'|head -$num"
#    ssh `findip -f $cserv` "clear; tput civis; while true; do tput cpu 0 0; ps $popt --sort=$sopt|egrep -v 'ps '$popt' --sort'|head -$num; sleep 2; done"
}

function sdproxy()
{
    iname=''
    iport=8088
    ikill=0
    ioff=0
    until [[ `echo $1` == '' ]]
    do
	case $1 in
	    -p) shift;iport=$1;shift;;
	    -k) ikill=1;shift;;
	    -o) ioff=1;shift;;
	    *) iname=$1;shift;;
	esac
    done
    if [ $ikill = 1 ]; then
	klist=`ssh $ihost 'ps ax'|egrep 'tail -f /etc/motd'|awk '{print $1}'`
	[[ $klist != '' ]] && ssh $ihost kill $klist
    fi
    ihost=`findip $iname`
    iuid=`ps ax|egrep "ssh -f -[DL] $iport"|egrep -v 'egrep'|awk '{print $1}'`
    [[ $iuid != '' ]] && echo 'Port '$iport' already in use, try to kill the present port forwarding' && kill $iuid
    [ $ioff != 1 ] && ssh -f -D $iport $ihost tail -f /etc/motd && echo 'Port forwarding: '$ihost' ---> 127.0.0.1:'$iport
}
