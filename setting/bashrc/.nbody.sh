#!/bin/bash
#checkcall
[ -e ~/src/scripts/checkcall.sh ] && source ~/src/scripts/checkcall.sh
function gcall()
{
    egrep -i 'call '$1'\>' *.[fF]
}

function ntime()
{
    egrep -m 1 '\<PE +N' $1
    egrep -A 1 '\<PE +N' $1|sed '{/PE/d ; /--/d}'
}
function radius()
{
    egrep -m 1 '^\ +<R>' $1
    egrep -A 1 '^\ +<R>' $1|sed '{/<R>/d ; /--/d}'
}
function nboutput()
{
    tflag='y'
    file=''
    until [[ $1 == '' ]];
    do
	case $1 in
	    -nt) tflag='n';shift;;
	    *) file=$1;shift;;
	esac
    done
    [[ $tflag == 'y' ]] && echo 'rank Time[NB] N <NB> NKS NMERGE MULT NS DE E <R> RTIDE RDENS RC NC MC RHOD RHOM CMAX <Cn> Ir/R UN NP R CM VCM AZ EB/E EM/E TCR T6 NESC VRMS'
    [[ $file != '' ]] && egrep -A 1 -B 2 '^\ +<R>' $file |sed 's/\(NSTEPS =\)\([- 0-9]\+\)\( DE\)/\3/g' |sed -e '/^$/d' -e '/<R>/d' -e '/--/d' -e 's/\<[a-zA-Z]\+\>//g' -e 's/#1//g' -e 's:[=<>/\t]::g'|sed -e '$!N;s/\n/ /' -e 's/ \+/ /g'
}

#Split sev.83 or bev.82 to individual snapshot
function splitse()
{
    path=''
    name=''
    num=0
    until [[ $1 == '' ]];
    do
	case $1 in
	    -p) shift;path=$1;shift;;
	    -n) shift;num=$1;shift;;
	    *) name=$1;shift;;
	esac
    done
    [[ $path == '' ]] && path=$name
    [[ $name == '' ]] && echo 'Need new file name' && return
    echo 'Split '$path' to '$name'.*+'$num
    awk "/[0-9]+ +[0-9\.]+ *$/{g++} { print \$0 > \"$name.\"g+$num}" $path
}

function splitseall
{
    [ -e dlist ] || return
    [ -d sse ] || mkdir sse
    echo 'Split sev.83'
    splitse -p sev.83 sse/sev
    lst=`cat dlist`
    for i in $lst
    do
	line=`ls sse|wc -l`
	splitse -p $i/sev.83 -n $line sse/sev
    done

    [ -d bse ] || mkdir bse
    echo 'Split bev.82'
    splitse -p bev.82 bse/bev
    lst=`cat dlist`
    for i in $lst
    do
	line=`ls bse|wc -l`
	splitse -p $i/bev.82 -n $line bse/bev
    done
}

alias adjust='egrep ADJUST'
alias escape='egrep -i escape'
alias ks='egrep -i "\<ks\>" '
alias nb='egrep -i "<NB>" '
alias rscale='egrep -i rscale'

#get information from main output
function getdata()
{
#    outfile=$1
    echo 'Read file: joblist (the paths of all output files)'
    [ -e joblist ] || return
#    [ -e tlabel ] || return

    lst=`cat joblist`
#from lagr.f
#     target='RLAGR AVMASS RSLAGR RBLAGR NPARTC SIGR2 SIGT2 VROT'
#     for j in $target
#     do
# 	[ -e $j ] && rm  $j
# 	cat tlabel > $j
# 	egrep $j $outfile|sed 's/D/E/g' >>$j
# 	for i in $lst
# 	do
# 	    egrep $j $i/$outfile |sed 's/D/E/g' >> $j
# 	done
#     done
#from main output
    [ -e nbout ] && rm nbout
    nboutput >>nbout
    for i in $lst
    do
	nboutput -nt $i >>nbout
    done
#adjust
    [ -e Adjust ] && rm Adjust
    for i in $lst
    do
	adjust $i  >>Adjust
    done
}

function getlagr()
{
    echo 'Read file: dirlist (the paths of all run directories)'
    [ -e dirlist ] || return

    lst=`cat dirlist`
    rm lagr
    for i in $lst
    do
	cat $i/lagr.7 >>lagr
    done
}

function bindata()
{
    echo 'Read file: dirlist (the paths of all run directories)'
    [ -e dirlist ] || return

    lst=`cat dirlist`

    [ -e bndat ] && rm bndat
    for i in $lst
    do
	for k in "bwdat.19" "bdat.9"
	do
	    ls $i/$k'_'*|cut -d'_' -f2|sort -n|awk "{print \"$i/$k\"\"_\"\$1}" >dtmplist_$k
	done
	lwnum=`wc -l dtmplist_bwdat.19|cut -d' ' -f1`
	lnum=`wc -l dtmplist_bdat.9|cut -d' ' -f1`
	echo $lwnum' '$lnum
	[ $lnum != $lwnum ] && return
	for ((j=1;j<=$lnum;j=j+1))
	do
	    bwfile=`sed -n "$j p" dtmplist_bwdat.19`
	    bwnum=`wc -l $bwfile|cut -d' ' -f1`
	    bfile=`sed -n "$j p" dtmplist_bdat.9`
	    bnum=`wc -l $bfile|cut -d' ' -f1`
	    echo `sed -n "$j p" dtmplist_bwdat.19|cut -d'_' -f2`' '`expr $bnum - 4`' '`expr $bwnum - 2` >> bndat
	done
    done
}

