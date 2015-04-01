#get x-ray luminouse binary

# if [ -e bindat/wd_binary.lst ]; then
#     [ -e xlb_wd ] && rm -i xlb_wd
#     lst=`cat bindat/wd_binary.lst`
#     for i in $lst
#     do
# 	time=`echo $i|cut -d'.' -f2-3`
# 	awk -v time=$time '{if ($15<10) {q=$4/$3; ro=0.49*q^(2.0/3.0)/(0.6*q^(2.0/3.0)+log(1+q^(1.0/3.0)));ri=ro*$11*(1-$12)/0.0046491; if (ri<$21) {tmp=""; for (i=1;i<=NF;i=i+1) {tmp=tmp" "$i}; print time,ri,tmp; }} else if ($14<10) {q=$3/$4; ro=0.49*q^(2.0/3.0)/(0.6*q^(2.0/3.0)+log(1+q^(1.0/3.0))); ri=ro*$11*(1-$12)/0.0046491; if (ri<$20) {tmp=""; for (i=5;i<=13;i=i+1) {tmp=tmp" "$i}; print time,ri,$2,$1,$4,$3,tmp,$15,$14,$17,$16,$19,$18,$21,$20;}}}' bindat/$i >xlb_wd_tmp
# 	if [ `wc -l xlb_wd_tmp|cut -d' ' -f1` -gt 0 ]; then
# 	    cat xlb_wd_tmp >>xlb_wd
# 	    echo "">>xlb_wd
# 	    echo "">>xlb_wd
# 	fi
# 	echo "Time = "$time
#     done
# fi

if [ -e bindat/ns_binary.lst ]; then
    [ -e xlb_ns ] && rm -i xlb_ns
    lst=`cat bindat/ns_binary.lst`
    for i in $lst
    do
	time=`echo $i|cut -d'.' -f2-3`
	awk -v time=$time '{if ($15<10) {q=$4/$3; ro=0.49*q^(2.0/3.0)/(0.6*q^(2.0/3.0)+log(1+q^(1.0/3.0)));ri=ro*$11*(1-$12)/0.0046491; if (ri<$21) {tmp=""; for (i=1;i<=NF;i=i+1) {tmp=tmp" "$i}; print time,ri,tmp; }} else if ($14<10) {q=$3/$4; ro=0.49*q^(2.0/3.0)/(0.6*q^(2.0/3.0)+log(1+q^(1.0/3.0))); ri=ro*$11*(1-$12)/0.0046491; if (ri<$20) {tmp=""; for (i=5;i<=13;i=i+1) {tmp=tmp" "$i}; print time,ri,$2,$1,$4,$3,tmp,$15,$14,$17,$16,$19,$18,$21,$20;}}}' bindat/$i >xlb_ns_tmp
	if [ `wc -l xlb_ns_tmp|cut -d' ' -f1` -gt 0 ]; then
	    cat xlb_ns_tmp >>xlb_ns
	    echo "">>xlb_ns
	    echo "">>xlb_ns
	fi
	echo "Time = "$time
    done
fi

if [ -e bindat/bh_binary.lst ]; then
    [ -e xlb_bh ] && rm -i xlb_bh
    lst=`cat bindat/bh_binary.lst`
    for i in $lst
    do
	time=`echo $i|cut -d'.' -f2-3`
	awk -v time=$time '{if ($15<13) {q=$4/$3; ro=0.49*q^(2.0/3.0)/(0.6*q^(2.0/3.0)+log(1+q^(1.0/3.0)));ri=ro*$11*(1-$12)/0.0046491; if (ri<$21) {tmp=""; for (i=1;i<=NF;i=i+1) {tmp=tmp" "$i}; print time,ri,tmp; }} else if ($14<13) {q=$3/$4; ro=0.49*q^(2.0/3.0)/(0.6*q^(2.0/3.0)+log(1+q^(1.0/3.0))); ri=ro*$11*(1-$12)/0.0046491; if (ri<$20) {tmp=""; for (i=5;i<=13;i=i+1) {tmp=tmp" "$i}; print time,ri,$2,$1,$4,$3,tmp,$15,$14,$17,$16,$19,$18,$21,$20;}}}' bindat/$i >xlb_bh_tmp
	if [ `wc -l xlb_bh_tmp|cut -d' ' -f1` -gt 0 ]; then
	    cat xlb_bh_tmp >>xlb_bh
	    echo "">>xlb_bh
	    echo "">>xlb_bh
	fi
	echo "Time = "$time
    done
fi
