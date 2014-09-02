#!/bin/bash

input=input.t.ref
sub=nbd6++.sub

ttt=1

for nstar in 16000 32000 64000 128000 256000
do
    ttt=`expr $ttt + 2`
    for nnn in 1 2 4 8 16 24 32
    do
	dirname=$nstar'_'$nnn
	[ -d $dirname ] || mkdir $dirname
	cd $dirname
	cp ../$input ./input
	cp ../$sub ./
	sed -i 's/nstar/'$nstar'/g' input
	sed -i 's/nnn/'$nnn'/g' $sub
	sed -i 's/ttt/'$ttt'/g' $sub
 	msub $sub
	cd ..
    done
done
