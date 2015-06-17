#paste band and color information
#require dlist

[ -e dlist ] || (echo 'dlist not exist' && exit 1)||exit

lst=`cat dlist|cut -d' ' -f1`

rm -f sbclst
for i in $lst
do
    paste $i.sb.B $i.sb.V $i.sb.I |awk 'BEGIN{print "r[pc] r[arcsec] S_B(mag/arcsec^2) S_V(mag/arcsec^2) S_I(mag/arcsec^2) B-V V-I"}{print $1,$3,$4,$11,$18,$4-$11,$11-$18}' >$i.color
    echo $i.color >>sbclst
done
