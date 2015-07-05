lst=`cut -d' ' -f1 sblst.V`

for i in $lst
do
    paste $i'.smooth_sb' $i'.smooth_sd' |awk '{if (NR>4) {print $1,$2,$5}}' >$i'.smooth'
done
