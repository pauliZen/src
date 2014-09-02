echo 'filename'
read file
rm -f labellist.log
rm -f m31distreg.list
index=0
num=`cat $file|wc -l`
for ((i=1;i<=num;i=i+1))
do
    echk=`head -$i $file |tail -1|cut -d' ' -f1`
    if [ $echk = "#" ]; then
	label=`head -$i $file |tail -1|sed 's/\ /_/g'|sed 's/://g'|cut -d'_' -f2-`
	index=`calc + $index 1`
	echo $index' '$label>>labellist.log
    else
	echo `head -$i $file |tail -1|cut -d'#' -f1`$index>>m31distreg.list
    fi
done
#datatoroot m31distreg
