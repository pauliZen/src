# need dirlist.lst
if [ -e dirlist.lst ]; then
    list=`cat dirlist.lst`
    for i in $list
    do
	pmax=`tail -1 $i-dat.lst`
	ibh1=999998
	ibh2=999999
	echo $i' '$pmax' '$ibh1' '$ibh2
	getinfradius $i $pmax $ibh1 $ibh2
    done
else
    echo 'drawlist.lst not found!'
fi
