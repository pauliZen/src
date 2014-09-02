echo 'dirlist offset nmax datapath isfirst(y/n)'
read dirlist offset nmax datapath isfirst

[ -e $dirlist ] || return
lst=`cat $dirlist`

[ -d $datapath ] || mkdir $datapath
[ -e $datapath/mloss ] && rm $datapath/mloss
[ -e $datapath/lagr_c ] && rm $datapath/lagr_c

for i in $lst
do
    ls $i/conf.3_*|cut -d'_' -f2|sort -n|awk "{print \"$i/conf.3_\"\$1}" >>tmplist
    flst=`cat tmplist`
    rm -f tmplist
    for j in $flst
    do
	time=`echo $j|cut -d'_' -f2`
	if [[ $isfirst == 'y' ]]; then
	    calcconf3 $j $offset $nmax 0 -1.0 1 $datapath/mloss 1 $datapath/mm0_$time 1 $datapath/lagr_c 1 $datapath/den_$time $datapath/denb_$time 0
	    isfirst='n'
	else
	    calcconf3 $j $offset $nmax 1 -1.0 1 $datapath/mloss 1 $datapath/mm0_$time 1 $datapath/lagr_c 1 $datapath/den_$time $datapath/denb_$time 0
	fi
    done
done
