MAXNB=20
MAXPERNB=5
nb=nbody6++.avx.gpu.mpi.hdf5

ILOOP=`expr $MAXNB / $MAXPERNB`
echo 'Looping '$ILOOP' times'
echo '3 1E6 1E6 40 40 0' >rs_ref
echo '0.0 0.0 0.0 0.0 '$MAXPERNB' 0.0 0 0' >>rs_ref
last=`ls|egrep rs[0-9]|cut -d's' -f2|sort -n|tail -1`
echo 'Last index '$last
ilast=$last
lst=`seq $ILOOP`
for k in $lst
do
    i=`expr $k + $last`
    mkdir rs$i
    cp rs_ref rs$i/rs
    ln -sf rs$ilast/fort.2 fort.1
    cp fort.1 rs$i/
    cd rs$i
    $nb <rs 1>o1 2>o2 
    ilast=$i
    cd ..
done
