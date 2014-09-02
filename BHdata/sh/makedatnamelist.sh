# make dat.extra name list for star-data-log-select   #
# using in root directory                             #

rootdir="/home/lwang/data/BHdata/nonrot/"

if [ -e dirlist.lst ];then
    num=`wc -l dirlist.lst|cut -d' ' -f1`
    for ((i=1;i<=$num;i=i+1))
    do
	name=`head -$i dirlist.lst|tail -1`
	if [ -e $rootdir$name ];then
	    ls $rootdir$name'/'[0-9]*.dat.extra|cut -d'.' -f1|cut -d'/' -f8>$name'-dat.lst'
#	echo $name' finished'
	else
	    echo 'No such directory '$rootdir$name
	fi
    done
else
    echo 'No dirlist.lst'
fi
