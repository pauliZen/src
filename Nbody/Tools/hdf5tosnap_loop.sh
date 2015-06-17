# transform hdf5 to data format for projection

[ -e snap.lst ] || exit
[ -e hdf5tosnap.py ] || exit

nloop=4
tscale=0.5506
dt=50.0
tint=0.125

ic=`wc -l snap.lst|cut -d' ' -f1`
lnum=`expr $ic / $nloop`
let lnum++

rm -f snap_split.*

split -a 1 -d -l $lnum snap.lst snap_split.

lst=`ls snap_split.*`
for i in $lst
do
    python hdf5tosnap.py $i $tscale $dt $tint 1>$i'.hdf5tosnap.log' 2>&1 &
done
