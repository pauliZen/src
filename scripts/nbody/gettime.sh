#!/bin/bash

list=`ls|egrep -i '[0-9]_[0-9]'`

rm -f time.*

for i in $list
do
    if [ -e $i/run.log ] && [ -e $i/my-out* ]; then
    	tnum=`egrep -A 1 'PE  N' $i/run.log|egrep -v 'PE  N'|sed '/--/d'|wc -l`
	for ((j=0;j<$tnum;j=j+1))
	do
	    jj=`expr $j + 1`
	    egrep -A 1 'PE  N' $i/run.log|egrep -v 'PE  N'|sed '/--/d'|sed 's/256000/\ 256000/g'|sed 's/128000/\ 128000/g'|head -$jj|tail -1 >>time.$j
	done
    fi
done
