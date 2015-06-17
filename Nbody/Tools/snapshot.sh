echo 'dirlist datapath=data output_prefix=data'
dirlist=dirlist
datapath=snap
output_prefix=data
offset=1  #binary format offset
nmax=200000
amax=50000  #maximum semi-major
fflag=1   #1 for Fit transformation; 2 for MOCCA
bflag=1   #1 for binary; 0 for no binary

lst=`cat $dirlist`

[ -d $datapath ] || mkdir $datapath
for i in $lst
do
    ls $i/conf.3_*|cut -d'_' -f2|sort -n >tmplist
    flst=`cat tmplist`
    rm -f tmplist
    for j in $flst
    do 
	time=$j
	if [ $fflag -eq 2 ]; then
	    output=$output_prefix"_"$time
	else
	    output=$output_prefix
	fi
	echo $i' '$j
	snapshot $time $datapath/$output $offset $nmax $amax $fflag $bflag $i
    done
done
