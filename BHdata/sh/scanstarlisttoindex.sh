#Scan star list to index---------------------------------#
#function: Transform scan file [dirname]-select-star.lst #
#          to index list file [dirname]-select-star.index#
#          for all listed in dirlist.lst                 #
#Notes: scan file structure: index:-dE/E_start:E_start   #
#       Should used in root file directory               #
#       Need dirlist.lst, [dirname]-select-star.lst      #

if [ -e dirlist.lst ];then
    num=`wc -l dirlist.lst|cut -d' ' -f1`
    for ((i=1;i<=$num;i=i+1))
    do
	name=`head -$i dirlist.lst|tail -1`
	namein=$name'-select-star.lst'
	if [ -e $namein ]; then
	    nameout=$name'-select-star.index'
	    cat $namein |cut -d'*' -f3|egrep '  [0-9]+' > $nameout
	else
	    echo 'No '$namein
	fi
    done
else
    echo 'No dirlist.lst'
fi
