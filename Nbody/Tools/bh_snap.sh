[ -e data.lst ] || exit
[ -d bhdata ] || mkdir bhdata

lst=`cat data.lst`

for i in $lst
do
    time=`echo $i|cut -d'_' -f2`
    awk 'BEGIN{lnum=0} {if ($14>0) {if ($19==14||$20==14) {print "b "lnum" "lnum+1" "$13" "$14" "($13*$1+$14*$7)/($13+$14)" "($13*$2+$14*$8)/($13+$14)" "($13*$3+$14*$9)/($13+$14)" "($13*$4+$14*$10)/($13+$14)" "($13*$5+$14*$11)/($13+$14)" "($13*$6+$14*$12)/($13+$14)" "$21" "$22" "58.1244*$21*sqrt(($21>0?$21:-$21)/($13+$14))" "$19" "$20; lnum++; lnum++}} else {if ($19==14) {print "s "lnum" "$13" "$1" "$2" "$3" "$4" "$5" "$6; lnum++}}}' $i >tmp.data
    egrep 'b ' tmp.data|sed 's/b //g' > bhdata/bh_binary.$time
    egrep 's ' tmp.data|sed 's/s //g' > bhdata/bh_single.$time
    [ `wc -l bhdata/bh_binary.$time|cut -d' ' -f1` -eq 0 ] && rm -f bhdata/bh_binary.$time
    [ `wc -l bhdata/bh_single.$time|cut -d' ' -f1` -eq 0 ] && rm -f bhdata/bh_single.$time
done
