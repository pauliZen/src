#transform bh-param.dat to root format.------------------#
# Used in the root directory and will run for all -------#
# subdirectory and store to root directory---------------#

rootdir="/home/lwang/data/BHdata/nonrot/"
if [ -e dirlist.lst ];then
    num=`wc -l dirlist.lst|cut -d' ' -f1`
    for ((i=1;i<=$num;i=i+1))
    do
	name=`head -$i dirlist.lst|tail -1`
	if [ -e $rootdir$name ];then
	    pardatatoroot $rootdir$name'/bh-param' './'$name'-bhpar'
	echo $name' finished'
	else
	    echo 'No such directory '$rootdir$name
	fi
    done
else
    echo 'No dirlist.lst'
fi
