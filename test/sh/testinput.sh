function testin()
    {
	sfile=""
	tfile=""
	until [[ `echo $1` == '' ]]
	do
	    case $1 in
		*) sfile=$sfile' '$tfile;tfile=$1;shift;;
	    esac
	done
	echo $sfile'->'$tfile
    }
    