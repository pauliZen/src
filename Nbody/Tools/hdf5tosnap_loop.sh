# transform hdf5 to data format for projection
# remove previous data first

echo 'If this is already did before, please remove the previous data since the file is open as append'
read -p 'Snapshot list file (snap.lst):' flist
read -p 'Hdf5 to snapshot script file (hdf5tosnap.py):' pscript
read -p 'Time scaling (1.0):' tscale
read -p 'Time interval (50.0):' dt
read -p 'Time resolution (0.125):' tint
read -p 'Parallel loop (4):' nloop

[[ -z $flist ]] && flist='snap.lst'
[[ -z $pscript ]] && pscript='hdf5tosnap.py'
[[ -z $nloop ]] && nloop=4
[[ -z $tscale ]] && tscale=1.0
[[ -z $dt ]] && dt=50.0
[[ -z $tint ]] && tint=0.125

[ -e $flist ] || (echo $flist' not exist' && exit 1) || exit
[ -e $pscript ] || (echo $pscript' not exist' && exit 1) || exit

ic=`wc -l $flist|cut -d' ' -f1`
lnum=`expr $ic / $nloop`
let lnum++

rm -f snap_split.*

split -a 1 -d -l $lnum $flist snap_split.

lst=`ls snap_split.*`
for i in $lst
do
    python $pscript $i $tscale $dt $tint 1>$i'.hdf5tosnap.log' 2>&1 &
done
