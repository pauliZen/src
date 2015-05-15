[ -e snap.lst ] || exit

split snap.lst -a 4 -d -l 50 snap_lst.

lst=`ls snap_lst.[0-9][0-9][0-9][0-9]`
hdflag=1
fsnap=1
fpr='data_'
bflag=1
rscale=1
mscale=1
vscale=1
fshell=1
fbres=0
Tint=1.0
Tres=0.125
libpath=/u/longw/lib/liblagr.so

[ -e lagr.snap ] && rm -f lagr.snap

for i in $lst
do
    t=`echo $i|cut -d'.' -f2`
    python lagrc.py $i $hdflag $fsnap $fpr $bflag $rscale $mscale $vscale $fshell $fbres $Tint $Tres $libpath >> lagr.snap 2>>lagr.err
done
#python lagrc.py snap_lst.0 $hdflag $fsnap $fpr $bflag $rscale $mscale $vscale $fshell $fbres $Tint $Tres $libpath
