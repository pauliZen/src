splitnum=5

ls |egrep ^[0-9]+_[0-9\.]+_[0-9\.]+_[0-9\.]+_[0-9]+_[0-9]+>v4list
ls |egrep ^[0-9]+_[0-9\.]+_[0-9\.]+_[0-9\.]+_[0-9]+$>v0list

cat v0list |awk '{print $1" "$1}'|sed 's/_/ /g5'>fitnsv0.lst
cat v4list |awk '{print $1" "$1}'|sed 's/_/ /g7'>fitnsv4.lst

l0num=`wc -l fitnsv0.lst|cut -d' ' -f1`
l4num=`wc -l fitnsv4.lst|cut -d' ' -f1`

p0num=`expr $l0num / $splitnum + 1`
p4num=`expr $l4num / $splitnum + 1`

split -d -a 1 -l $p0num fitnsv0.lst fitnsv0
split -d -a 1 -l $p4num fitnsv4.lst fitnsv4

for ((i=1;i<=$splitnum;i=i+1))
do
    fitnsnp fitnsv0$i nsfit_v0$i.root 0 1>fitnsnp_v0$i.log 2>&1 
    fitnsnp fitnsv4$i nsfit_v4$i.root 4 1>fitnsnp_v4$i.log 2>&1 
done
