function lps()
{
    if [ -e ~/.ssh/dragon.list ]; then
	num=10
	flag=0
	ssort='-%cpu,-%mem,-uid'
	option='aux'
	until [ $flag = 1 ];
	do
	    case $1 in
		-n) shift; num=$1;shift;;
		-s) shift; ssort=$1;shift;;
		-o) shift; option=$1;shift;;
		*) flag=1;;
	    esac
	done
	num=`expr $num + 1`
	dlist=`cat ~/.ssh/dragon.list`
	for i in $dlist
	do
	    iname=`echo $i|cut -d':' -f1`
	    ihost=`echo $i|cut -d':' -f2`
	    myname=`whoami`
	    echo -e "\033[43m\033[30m"$iname"-----------------------------------------------------------\033[0m"
	    if [[ $iname = `hostname|cut -d'.' -f1` ]]; then
		ps $option --sort=$ssort|egrep -v "ps "$option" --sort"|head -$num
	    else
		ssh $myname@$ihost "ps $option --sort=$ssort|egrep -v 'ps '$option' --sort'|head -$num"
	    fi
	done
    fi
}
