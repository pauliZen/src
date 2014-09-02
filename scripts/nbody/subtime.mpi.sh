#!/bin/bash

input=input.t.ref
sub=nb6++.mpi.sub

ttt=24

for nstar in 16000 32000 64000 128000 256000
do
#    ttt=`expr $ttt + 2`
    for nnn in 1 2 4 8 16 24 32
    do
	nss=$nnn
	dirname=$nstar'_'$nnn
	pnn=1
	[ $nnn -gt 8 ] && nnn=`expr $nnn / 8` && pnn=8
	[ -d $dirname ] || mkdir $dirname
	cd $dirname
	cp ../$input ./input
	cp ../$sub ./
	sed -i 's/nstar/'$nstar'/g' input
	sed -i 's/nnn/'$nnn'/g' $sub
	sed -i 's/pnn/'$pnn'/g' $sub
	sed -i 's/ttt/'$ttt'/g' $sub
	sed -i 's/nss/'$nss'/g' $sub
 	msub $sub
	cd ..
    done
done
