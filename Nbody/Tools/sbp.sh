# get surfacedensity and average value (require dlist)
# Preprogram: data_proj(_loop).sh

read -p 'Parallel number(4):' nloop
read -p 'data file list without .prj and time[Myr] (dlist)' flist

[[ -z $nloop ]] && nloop=4
[[ -z $flist ]] && flist='dlist'

[ -e surfacedensity.py ] || (echo 'surfacedensity.py not exist' && exit 1) || exit

ic=`wc -l dlist|cut -d' ' -f1`
lnum=`expr $ic / $nloop`
[ `expr $lnum \* $nloop` -lt $ic ] && let lnum++

rm -f slist.*

split -a 1 -d -l $lnum $flist slist.

function sloop()
{
    lst=`cat slist.$1`
    for j in $lst
    do
	echo "sbp $j"
	python surfacedensity.py $j.prj 'V' 100 25 0.1 $j.sb.V 5800 
	python surfacedensity.py $j.prj 'I' 100 25 0.1 $j.sb.I 5800 
	python surfacedensity.py $j.prj 'B' 100 25 0.1 $j.sb.B 5800
    done	
}

ic=`ls slist.*|wc -l`
for ((i=0;i<$ic;i=i+1))
do
    sloop $i >sbp.log.$i 2>&1 &
done
