# require data file list(without .prj) with time[myr] (dlist)
# fiting king profile for Rc and Rt

[ -e king-fit-lum.plt ] || exit

read -p 'Parallel number(4):' nloop
read -p 'Data file without .prj(dlist):' flist

[[ -z $nloop ]] && nloop=4
[[ -z $flist ]] && flist='dlist'

ic=`wc -l $flist|cut -d' ' -f1`
lnum=`expr $ic / $nloop`
let lnum++

rm -f dlst_split.*

split -a 1 -d -l $lnum $flist dlst_split.

lst=`ls dlst_split.*`
for i in $lst
do
    awk '{print $1".prj",$2}' $i > dlst
#  V filter
    echo 'V 4.83 18' >dpar
    gnuplot king-fit-lum.plt >$i.log 2>$i.err &
    sleep 5
done
