echo "dirlist output_datapath output_prefix"
read dirlist datapath output

[ -e $dirlist ] || return
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
	echo $i' '$j' '$output_prefix
    done
done
