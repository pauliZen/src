#--------------------------------------------------------#
#-Fortran call check code-written by Long Wang-----------#
#-Command: fcall [option] "subroutine name"--------------#
#-option: -i) show introcution---------------------------#
#         -h) help---------------------------------------#
#         -n [number]) order to check call---------------#
#--------------------------------------------------------#

introfile=`echo ~`'/data/Planets/intro.txt'
commentline=4

function ngetinfo()
{
    if [ $nintr = 1 ];then
	echo -e '\033[31m<--->\033[3'$2'm'
	if [ -e $introfile ];then
	    egrep -i ^$1 $introfile|cut -d'|' -f2
	else
	    head -$commentline $1|tail -1|cut -d'*' -f2
	fi
	echo -e '\033[0m'
    fi
}

function ncall()
{
    if [ $order = $depth ]; then
	jlist=`egrep -l -i "^[0-9\ ]+call\ +$1\>" *.[fF]`
	for jj in $jlist
	do
	    echo -e $sspc"\t\033[32m|---\033[0m"$jj" "`ngetinfo $jj 9 $nintr`
	done
    else
	let order++
	list=`egrep -l -i "^[0-9\ ]+call\ +$1\>" *.[fF]|sed 's/\.[fF]//g'`
	for i in $list
	do
	    sspc=""
	    for ((j=1;j<$order;j=j+1))
	    do
		sspc="\t\033[32m|\033[0m"$sspc
	    done
	    echo -e $sspc"\033[32m---\033[4"$order"m\033[30m"$i'.f\033[0m '$order' '`ngetinfo $i'.f' $order $nintr`
	    ncall $i
	done
	let order--
    fi
}

function fcall()
{
    depth=1
    optend=0
    name=""
    sspc=""
    nintr=0
    until [ $optend = 1 ];
    do
	case $1 in
	    -h) echo 'check call function for fortran source code. checkall [-n depth] name';optend=1;return;;
	    -n) shift;depth=$1;shift;;
	    -i) shift;nintr=1;;
	    *) name=$1;optend=1;;
	esac
    done
    order=1
    echo -e '\033[32m----\033[45m'$name'.f\033[0m'`ngetinfo $1'.f' 1 $nintr`
    ncall $name
}

# call check for all list
function fcallcheck()
{
    flist=`ls *.[fF]|egrep "^[a-zA-Z0-9_\-]+\.[fF]"`
    filename=`egrep -li "(subroutine|function)\ +\<$1\>" $flist|head -1`
    list=`egrep -i '\<call ' $filename|egrep -v "^[*cC]"|sed 's/.*call \(.*\)[($]*/\1/gi; s/(.*//g'|sort|uniq`
    for j in $list
    do
	fname=`egrep -li "(subroutine|function)\ +\<$j\>" $flist|head -1|sed 's/\.[fF]//g'`
	isinside=`echo $globallist|egrep -ic "\<$fname\>"`
	sspc=""
	for ((k=0;k<$order;k=k+1))
	do
	    sspc="\t\033[32m|\033[0m"$sspc
	done
	if [ $isinside = 0 ]; then
	    echo -e $sspc"\033[32m---\033[4"$order"m\033[30m"$fname"\033[0m"
	    globallist=$fname' '$globallist
	    let order++
	    fcallcheck $j
	    let order--
	else
	    [ $showall = 1 ] && echo -e $sspc"\033[32m---\033[0m"$fname'\033[45m[Repeat]\033[0m'
	fi
    done
}

function fcalllist()
{
    name=""
    optend=0
    order=1
    showall=0
    until [ $optend = 1 ];
    do
	case $1 in
	    -h) echo 'check call function for fortran source code. checkall [-n depth] name; fcallcheck name';optend=1;return;;
	    -a) showall=1;shift;;
	    *) name=$1;optend=1;;
	esac
    done
    globallist=$name
    echo -e '\033[32m----\033[45m'$name'\033[0m'
    fcallcheck $name
    echo -e '\033[32mAll subroutine:\033[0m'
    echo $globallist
}
    