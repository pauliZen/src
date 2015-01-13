echo "dirlist filename headerlines ncolumn outputfile headerrepeatflag"
read dname fname nh nc nfile hflag
[ -e $nfile ] && rm -i $nfile
lst=`cat $dname`
[ $hflag -eq 0 ] && head -$nh `head -1 $dname`/$fname >$nfile
bflag=1
for k in $lst
do
    if [ $hflag -eq 1 ] || [ $bflag -eq 1 ]; then
	bflag=0;
	sed -n "$nh,\$ p" $k/$fname| awk -v tmp="$tmp" -v ncc="$ncc" "{for (i=0;i<NF;i++) {if(ncc<$nc) {tmp=tmp\" \"\$i; ncc++;} else {print tmp; ncc=0; tmp=\"\"}}}" >>$nfile
    else
	awk -v tmp="$tmp" -v ncc="$ncc" "{for (i=0;i<NF;i++) {if(ncc<$nc) {tmp=tmp\" \"\$i; ncc++;} else {print tmp; ncc=0; tmp=\"\"}}}" $k/$fname >>$nfile
    fi
done
