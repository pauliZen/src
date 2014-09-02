lines=`cat ref.txt|wc -l`
files=`cat Uodf.lst|wc -l`
if [ -e shift.txt ];then
    rm shift.txt
fi
for ((j=1;j<=$files;j=j+1))
do
    nowfile=`head -$j Uodf.lst|tail -1|cut -b8-9`'.lst'
    x=0
    y=0
    for ((i=1;i<=$lines;i=i+1))
    do
	if [ -e $nowfile ];then
	    xtmp=`head -$i $nowfile|tail -1|cut -d' ' -f1`
	    ytmp=`head -$i $nowfile|tail -1|cut -d' ' -f2`
	    echo $xtmp $ytmp $nowfile
	    x=`calc + $x $xtmp`
	    y=`calc + $y $ytmp`
	else
	    x=0
	    y=0
	fi
    done
    x=`calc / $x $lines`
    y=`calc / $y $lines`
    echo $x $y>>shift.txt
done
