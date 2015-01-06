fdir='data2'
lst=`ls $fdir|grep 'data_[0-9]'|cut -d'_' -f2|sort -n`
[ -e ebin.dat ] && rm -i ebin.dat
for i in $lst
do
    echo 'Now Time='$i
    eb=`awk 'BEGIN{ebin=0.0;} {if ($14>0 && $21>0) {ebin=ebin+(0.000923285)*$13*$14/$21;}} END{print ebin}' $fdir/data_$i`
    echo `calc \* $i 0.6223751203866`' '$eb >> ebin.dat
done
