[ -e dirlist ] || exit

[ -e snap.lst ] && rm -i snap.lst

lst=`sed -n '2,$ p' dirlist`
for i in $lst
do
    tmp=`ls $i/snap*|cut -d'_' -f2 |cut -d'.' -f1|sort -n`
    [[ x$last != x`echo $tmp|awk '{print $1}'` ]] && [[ x$last != x ]] && echo $lastpath >>snap.lst
    last=`echo $tmp|awk '{print $NF}'`
    lastpath="$i/snap.40_$last.h5part"
    for j in $tmp
    do
	[[ x$j != x$last ]] && echo $i/snap.40_$j.h5part >>snap.lst
    done
done
