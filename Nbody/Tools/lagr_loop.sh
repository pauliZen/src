# calculating lagrangian radii
# require data files

rscale=1.0
mscale=1.0
vscale=1.0
bflag=1
fsnap=1
fpr='data_'

read -p 'Parallel number (4):' nloop
[[ -z $nloop ]] && nloop=4
read -p 'Snapshot list (snap.lst):' flist
read -p 'HDF5? y/n (y):' hdflag

[[ -z $hdflag ]] && hdflag=1
if [[ $hdflag == 'n' ]]; then
    hdflag=0
    read -p 'Snapshot file for projection? y/n (y):' fsnap
    [[ -z $fsnap ]] && fsnap=1
    if [[ $fsnap == 'n' ]]; then
	fsnap=0
	read -p 'Is binary exist? y/n (y):' bflag
	[[ -z $bflag ]] && bflag=1
	if [[ $bflag == 'n' ]]; then
	    bflag=0
	else
	    bflag=1
	fi
	read -p 'Radius scaling (1.0):' rscale
	[[ -z $rscale ]] && rscale=1.0
	read -p 'Mass scaling (1.0):' mscale
	[[ -z $mscale ]] && mscale=1.0
	read -p 'Velocity scaling (1.0):' vscale
	[[ -z $vscale ]] && vscale=1.0
    else
	fsnap=1
    fi
    read -p 'Datafile prefix: for projection data filename is [prefix][item in snap.lst]; for MOCCA data filename is [prefix][item in snap.lst]_(binary|single).dat (data_):' fpr
    [[ -z $fpr ]] && fpr='data_'
else
    hdflag=1
fi

read -p 'Whether calculate for shells y/n (y):' fshell
[[ -z $fshell ]] && fshell=1
[[ $fshell == 'n' ]] && fshell=0
read -p 'Whether resolve binaries for average mass calculation y/n (n):' fbres
[[ -z $fbres ]] && fbres=0
[[ $fbres == 'y' ]] && fbres=1
read -p 'Time interval for calculation in NB unit (1.0):' Tint
[[ -z $Tint ]] && Tint=1.0
read -p 'Resolution of snapshot in NB unit (0.125):' Tres
[[ -z $Tres ]] && Tres=0.125
read -p 'liblagr.so path (/u/longw/lib/liblagr.so):' libpath
[[ -z $libpath ]] && libpath=/u/longw/lib/liblagr.so

[ -e $flist ] || (echo $flist' not exist!' && exit 1) || exit

ic=`wc -l $flist|cut -d' ' -f1`
lnum=`expr $ic / $nloop`
[ `expr $lnum \* $nloop` -lt $ic ] && let lnum++

rm -f snap_block.*
rm -f snap_lst_*

split -a 2 -d -l $lnum $flist snap_block.

function sloop()
{
    k=${1#*.}
    lst=`ls snap_lst_${k}.[0-9][0-9][0-9][0-9]`
    for ii in $lst
    do
	python lagrc.py $ii $hdflag $fsnap $fpr $bflag $rscale $mscale $vscale $fshell $fbres $Tint $Tres $libpath >> lagr.snap.$k 2>>lagr.err 
    done
}

blst=`ls snap_block.*`

for i in $blst
do

    split $i -a 4 -d -l 50 snap_lst_${i#*.}.
    sloop $i &
done

