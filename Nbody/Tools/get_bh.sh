[ -e dirlist ] || exit

[ -e number.dat ] && rm -i number.dat

lst=`cat dirlist`
for i in $lst
do
    echo 'processing '$i
    chlist=`ls $i/sev.83_*|cut -d'_' -f2|sort -n`
    for j in $chlist
    do
	sdata=`awk 'BEGIN{nns=0; nwd1=0; nwd2=0; nwd3=0; nbh=0} {if (NR==1) t=$2 ; if ($4==10) nwd1++; if ($4==11) nwd2++; if ($4==12) nwd3++; if ($4==13) nns++; if ($4==14) nbh++; } END{print t,nwd1,nwd2,nwd3,nns,nbh}' $i/sev.83_$j`
	bdata=`awk 'BEGIN{nns=0; nwd1=0; nwd2=0; nwd3=0; nbh=0} {if (NR==1) t=$2 ; if ($6==10 || $7==10) nwd1++; if ($6==11 || $7==11) nwd2++; if ($6==12 || $7==12) nwd3++; if ($6==13 || $7==13) nns++; if ($6==14 || $7==14) nbh++; } END{print nwd1,nwd2,nwd3,nns,nbh}' $i/bev.82_$j`
	echo $sdata' '$bdata >>number.dat
    done
done
