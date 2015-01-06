echo 'dirlist datapath=data output_prefix=data'
dirlist=dirlist
datapath=data2
output_prefix=data

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
	echo $i' '$j
	snapshot $time $datapath/$output_prefix 1 2000000 50 1 1 $i
    done
done
