ach='archive_list.sh'
achlist='ach.lst'
achdir="~/r/R7_B5_IMF2001"
pref='r7_b5'

[ -e $ach ] && rm -i $ach
[ -e $achlist ] || touch ach.lst

echo `ls ../init_thijsb/job.out.*` >joblist
echo "../init_thijsb" >dirlist

ncount=0
str=""

jobid=`ls job.out.**|cut -d'.' -f3|sort|uniq`
for i in $jobid
do
    lst=`ls job.out.$i.**|cut -d'.' -f4|sort -n`
    for j in $lst
    do
	echo job.out.$i.$j >> joblist
	echo rsll1-ib0.$i.$j >> dirlist
	if [ `egrep -c "$i.$j" $achlist` -eq 0 ]; then
	    str=$str" job.out.$i.$j job.err.$i.$j rsll1-ib0.$i.$j"
	    let ncount++
	    if [ $ncount -ge 7 ]; then
		echo "tar cvf "$pref."$i.$j".$ncount".tar "$str >>$ach
		echo 'echo '$str' >>'$achlist >>$ach
		echo 'mv '$pref."$i.$j".$ncount'.tar '$achdir' &' >>$ach
		ncount=0
		str=""
	    fi
	fi
    done
done
