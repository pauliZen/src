[ -e drawlist.lst ] || return
[ -e NT.root ] && rm -f NT.root

lnum=`wc -l drawlist.lst|cut -d' ' -f1`

for ((i=1;i<=$lnum;i=i+1))
do
    name=`head -$i drawlist.lst|tail -1|cut -d' ' -f1`
    bhmass1=`head -$i drawlist.lst|tail -1|cut -d' ' -f2`
    bhmass2=`head -$i drawlist.lst|tail -1|cut -d' ' -f3`
    ls $name-result-dE* >de.lst
    drawNT de.lst $name-bhpar.root destars $name-dNt $name-dNAt 250 0.003 150 0 150 10 1 $name-dEt 100 1E-6 1E-5 140 $bhmass1 $bhmass2 CONT1Z /home/lwang/Dropbox/Datas/BHdata/figures/NT/ NT.root eps
done
