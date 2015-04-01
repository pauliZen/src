#get binary number

if [ -e bindat/wd_binary.lst ]; then
    [ -e nbinwd ] && rm -i nbinwd
    lst=`cat bindat/wd_binary.lst`
    for i in $lst
    do
	time=`echo $i|cut -d'.' -f2-3`
	num=`wc -l bindat/$i|cut -d' ' -f1`
	echo $time' '$num >>nbinwd
    done
fi

if [ -e bindat/ns_binary.lst ]; then
    [ -e nbinns ] && rm -i nbinns
    lst=`cat bindat/ns_binary.lst`
    for i in $lst
    do
	time=`echo $i|cut -d'.' -f2-3`
	num=`wc -l bindat/$i|cut -d' ' -f1`
	echo $time' '$num >>nbinns
    done
fi

if [ -e bindat/bh_binary.lst ]; then
    [ -e nbinbh ] && rm -i nbinbh
    lst=`cat bindat/bh_binary.lst`
    for i in $lst
    do
	time=`echo $i|cut -d'.' -f2-3`
	num=`wc -l bindat/$i|cut -d' ' -f1`
	echo $time' '$num >>nbinbh
    done
fi
