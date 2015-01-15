#based on data from bh.py or bh_snap.sh
[ -e bh_single.lst ] || exit
lsts=`cat bh_single.lst`

[ -e bh_sall ] && rm -f bh_sall

for i in $lsts
do
    time=`echo $i|cut -d'.' -f2-3`
    cat $i|awk "{printf \$1\" \"$time\" \";for(i=2;i<=NF;i++){printf \$i\" \"}; printf \"\\n\"}" >>bh_sall
done
    
if [ -e bh_binary.lst ]; then
    lstb=`cat bh_binary.lst`
    [ -e bh_ball ] && rm -f bh_ball
    for i in $lstb
    do
	time=`echo $i|cut -d'.' -f2-3`
	cat $i |awk "{printf \$1\" \"\$2\" \"$time\" \";for(i=3;i<=NF;i++){printf \$i\" \"}; printf \"\\n\"}" >>bh_ball
    done
fi

if [ -e bh_merger.lst ]; then
    lstm=`cat bh_merger.lst`
    [ -e bh_mall ] && rm -f bh_mall
    for i in $lstm
    do 
	cat $i |awk "{print \$1\" \"\$2\" \"\$3\" \"$time\" \";for(i=4;i<=NF;i++){printf \$i\" \"}; printf \"\\n\"}">>bh_mall
    done
fi
