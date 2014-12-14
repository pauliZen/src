[ -e joblist ] || exit
[ -e ntime.dat ] && rm -i ntime.dat
lst=`cat joblist`
for i in $lst
do
    ntime $i >>ntime.dat
done
