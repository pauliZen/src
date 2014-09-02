#!/bin/bash

input=input.ref
sub=nb6++.sub

for nstar in 16000 24000
do
    for seed in 4234 212 5534
    do
	for sse in 0 3
	do
	    for etai in 0.02 0.01
	    do
		for etar in 0.02 0.01
		do
		    for imf in 0 2
		    do
			dirname=$nstar'_'$seed'_'$sse'_'$etai'_'$etar'_'$imf
			[ -d $dirname ] || mkdir $dirname
			cd $dirname
			cp ../$input ./input
			cp ../$sub ./
			sed -i 's/nstar/'$nstar'/g' input
			sed -i 's/seed/'$seed'/g' input
			sed -i 's/sse/'$sse'/g' input
			sed -i 's/etai/'$etai'/g' input
			sed -i 's/etar/'$etar'/g' input
			sed -i 's/imf/'$imf'/g' input
			msub $sub
			cd ..
		    done
		done
	    done
	done
    done
done
