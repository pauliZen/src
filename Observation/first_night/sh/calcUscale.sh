if [ -e Uscaled.txt ]||[ -e Udodfse.lst ];then
    rm U*odfse.lst
    rm Uscale*.txt
    echo 'delete origin'
fi
for ((i=1;i<=2;i=i+1))
do
    scale=`head -1 Urefstar.mag|tail -1|sed 's/ \+/|/g'|cut -d'|' -f2`
    now=`head -$i Urefstar.mag|tail -1|sed 's/ \+/|/g'|cut -d'|' -f2`
    head -$i Urefstar.mag|tail -1|sed 's/ \+/|/g'|cut -d'|' -f1>>Udodfse.lst
    calc / $scale $now >>Uscaled.txt
done
for ((i=3;i<=5;i=i+1))
do
    scale=`head -3 Urefstar.mag|tail -1|sed 's/ \+/|/g'|cut -d'|' -f2`
    now=`head -$i Urefstar.mag|tail -1|sed 's/ \+/|/g'|cut -d'|' -f2`
    calc / $scale $now >>Uscalei.txt
    head -$i Urefstar.mag|tail -1|sed 's/ \+/|/g'|cut -d'|' -f1>>Uiodfse.lst
done
for ((i=6;i<=7;i=i+1))
do
    scale=`head -6 Urefstar.mag|tail -1|sed 's/ \+/|/g'|cut -d'|' -f2`
    now=`head -$i Urefstar.mag|tail -1|sed 's/ \+/|/g'|cut -d'|' -f2`
    calc / $scale $now >>Uscalem.txt
    head -$i Urefstar.mag|tail -1|sed 's/ \+/|/g'|cut -d'|' -f1>>Umodfse.lst
done
