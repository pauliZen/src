# project group of data (require dlist (datafile name from hdf5tosnap results and time[Myr]))
# Preprogram: hdf5tosnap.py

pbin=mag_proj
z=0.00016
nloop=4

read -p 'program (mag_proj):' pbin
read -p 'parallel processes (4):' nloop
read -p 'metallicity (0.02)' z

[[ -z $pbin ]] && pbin=mag_proj
[[ -z $nloop ]] && nloop=4
[[ -z $z ]] && z=0.02

[ -e dlist ] || (echo 'dlist not exist' & exit 1) || exit

ic=`wc -l dlist|cut -d' ' -f1`
lnum=`expr $ic / $nloop`
let lnum++

rm -f dlist_split.*

split -a 1 -d -l $lnum dlist dlist_split.

function sloop()
{
    lst=`cat $1|awk '{print $1}'`
    for j in $lst
    do 
	echo "data_proj $j"
	echo "$j" >magin.$j
	echo "$j.prj" >>magin.$j
	echo "$z" >>magin.$j
	$pbin <magin.$j
	rm -f magin.$j
    done
}

llst=`ls dlist_split.*`

for i in $llst
do
    sloop $i >data_proj.log.${i#*.} 2>&1 &
done
