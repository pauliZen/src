#bhdatatoroot--------------------------------------------#
#function: transform all bh.dat to [dirname]-bh.root-----#
#          Use in root directory-------------------------#
#          Should exist dirlist.lst file of run-dir      #

rootdir="/data/lwang/BHdata/nonrot/"

if [ -e dirlist.lst ];then
    num=`wc -l dirlist.lst|cut -d' ' -f1`
    for ((i=1;i<=$num;i=i+1))
    do
	name=`head -$i dirlist.lst|tail -1`
	if [ -e $rootdir$name ];then
	    bhdatatoroot $rootdir$name'/' 'bh' './'$name'-bh'
	echo $name' finished'
	else
	    echo 'No such directory '$rootdir$name
	fi
    done
else
    echo 'No dirlist.lst'
fi
