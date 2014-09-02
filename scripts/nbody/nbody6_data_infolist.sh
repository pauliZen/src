echo Input script filename:
read inputsh
rm -f *_*.txt
mkdir info
ls -d *_*>datadirlist
nt=`egrep -c '*_*' datadirlist`
rm -f Info.txt
for ((i=1;i<=$nt;i=i+1))
do
    j=$i
    tmp=`head -$j datadirlist|tail -1`
    echo $tmp
    echo '*'$tmp'================================================*'>>Info.txt
    tail -1 $tmp/run.log>>Info.txt
    tail -1 $tmp/run.log>info/$tmp.txt
    echo '---------------------------------------------------------'>>Info.txt
    echo '---------------------------------------------------------'>>info/$tmp.txt
    fl=`egrep -n 'EOF' $tmp/$inputsh|cut -d":" -f1|head -1`
    el=`egrep -n 'EOF' $tmp/$inputsh|cut -d":" -f1|tail -1`
    tl=`expr $el - $fl`
    head -$el $tmp/$inputsh|tail -$tl>>Info.txt
    head -$el $tmp/$inputsh|tail -$tl>>info/$tmp.txt
done
rm -f datadirlist

