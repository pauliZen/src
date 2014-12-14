[ -e dirlist ] || return
lst=`cat dirlist`
offset=1
nmax=1500000
datapath=lagr

[ -d $datapath ] || mkdir $datapath
[ -e $datapath/mloss ] && rm $datapath/mloss
[ -e $datapath/lagr_c ] && rm $datapath/lagr_c

isfirst='y'
for i in $lst
do
    ls $i/conf.3_*|cut -d'_' -f2|sort -n|awk "{print \"$i/conf.3_\"\$1}" >>tmplist
    flst=`cat tmplist`
    rm -f tmplist
    for j in $flst
    do
	time=`echo $j|cut -d'_' -f2`
	if [[ $isfirst == 'n' ]]; then
	    calcconf3 $j $offset $nmax 0 -1.0 0 $datapath/mloss 0 $datapath/mm0_$time 1 $datapath/lagr_c 0 $datapath/den_$time $datapath/denb_$time 0
	    isfirst='y'
	else
	    calcconf3 $j $offset $nmax 1 -1.0 0 $datapath/mloss 0 $datapath/mm0_$time 1 $datapath/lagr_c 0 $datapath/den_$time $datapath/denb_$time 0
	fi
    done
done
