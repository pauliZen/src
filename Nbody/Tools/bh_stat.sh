#based on data from bh.py or bh_snap.sh
[ -e bh_single.lst ] || exit
lsts=`cat bh_single.lst`

[ -e bh_sdata ] && rm -f bh_sdata

for i in $lsts
do
    time=`echo $i|cut -d'.' -f2-3`
    data=`awk 'BEGIN{c=0;m=0;x1=0;x2=0;x3=0;v1=0;v2=0;v3=0} {c=c+1;m=m+$2;x1=x1+$2*$3;x2=x2+$2*$4;x3=x3+$2*$5;v1=v1+$2*$6;v2=v2+$2*$7;v3=v3+$2*$8} END{print c" "m/c" "x1/m" "x2/m" "x3/m" "v1/m" "v2/m" "v3/m}' $i`
    echo $time" "$data >>bh_sdata

done
    
if [ -e bh_binary.lst ]; then
    lstb=`cat bh_binary.lst`
    [ -e bh_bdata ] && rm -f bh_bdata
    for i in $lstb
    do
	time=`echo $i|cut -d'.' -f2-3`
	data=`awk 'BEGIN{bbc=0;c=0;m=0;x1=0;x2=0;x3=0;v1=0;v2=0;v3=0;e=0,ecc=0,p=0} {c=c+1;mtp=$3+$4;m=m+mtp;x1=x1+mtp*$5;x2=x2+mtp*$6;x3=x3+mtp*$7;v1=v1+mtp*$8;v2=v2+mtp*$9;v3=v3+mtp*$10;e=e+$3*$4/(2*$11);ecc=ecc+$12;p=p+$13;if($14==14 && $15==14) {bcc=bcc+1}} END{print c" "bbc" "m/c" "x1/m" "x2/m" "x3/m" "v1/m" "v2/m" "v3/m" "e/c" "ecc/c" "p/c}' $i`
	echo $time" "$data >>bh_bdata
    done
fi

if [ -e bh_merger.lst ]; then
    lstm=`cat bh_merger.lst`
    [ -e bh_mall ] && rm -f bh_mall
    for i in $lstm
    do 
	time=`echo $i|cut -d'.' -f2-3`
	data=`awk 'BEGIN{c=0;m=0;x1=0;x2=0;x3=0;v1=0;v2=0;v3=0} {c=c+1;mtp=$2+$3+$4;m=m+mtp;x1=x1+mtp*$5;x2=x2+mtp*$6;x3=x3+mtp*$7;v1=v1+mtp*$8;v2=v2+mtp*$9;v3=v3+mtp*$10} END{print c" "m/c" "x1/m" "x2/m" "x3/m" "v1/m" "v2/m" "v3/m}' $i`
	echo $time" "$data >>bh_mdata
    done
fi
