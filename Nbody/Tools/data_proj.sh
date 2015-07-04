# project group of data (require snap.lst for HDF5 data)
# Preprogram: hdf5tosnap.py

pbin=mag_proj
z=0.00016

[ -e snap.lst ] || exit

rm -f dlist.*
rm -f tlist.sb
lst=`cut -d'.' -f2 snap.lst|cut -d'_' -f2|sort -n`
ic=0
prev=-10
for i in $lst
do
    pnow=$i
    [[ x`expr $pnow - $prev` == 'x1' ]] || let ic++
    prev=$i
    ls data_$i.* >>dlist.$ic
done

for ((i=1;i<=$ic;i=i+1))
do
    lst=`cat dlist.$i`
    for j in $lst
    do
	echo "sbp $j"
	echo "$j" >magin
	echo "$j.prj" >>magin
	echo "$z" >>magin
	$pbin <magin
    done
done

