#totalenergychangequeue----------------------------------#
#function: calculate totalenergy by totalenergychange----#
#          Use in root directory-------------------------#
#          Should exist dirlist.lst file of run-dir------#
#          Should exist [dirname]-dat.lst----------------#

if [ -e dirlist.lst ];then
    num=`wc -l dirlist.lst|cut -d' ' -f1`
    for ((i=1;i<=$num;i=i+1))
    do
	dirname=`head -$i dirlist.lst|tail -1`
	if [ -e $dirname'-dat.lst' ];then
	    pf=`head -1 $dirname'-dat.lst'`
	    pd=`tail -1 $dirname'-dat.lst'`
	    total-energy-change $dirname P$pf P$pd E$pf"to"$pd "Energy&L_data_of_P"$pf"_and_P"$pd
#	echo $name' finished'
	else
	    echo 'No such directory '$dirname'-dat.lst'
	fi
    done
else
    echo 'No dirlist.lst'
fi
