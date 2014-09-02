#!/bin/bash

list=`ls|egrep -i '[0-9]_[0-9]'`

for i in $list
do
    [ -e $i/run.log ] && [ -e $i/my-out* ] && echo $i' '"`tail -1 $i/run.log`"
done
