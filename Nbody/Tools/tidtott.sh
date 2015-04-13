#!/bin/bash
echo 'File to transfer:'
read File
echo 'Time offset'
read TTOFF
NBTT=`wc -l $File |cut -d' ' -f1`
NBTT=`expr $NBTT - 1`
TTUNIT=14.91
echo $NBTT' '$TTUNIT' '$TTOFF >tt.dat
sed -n '2,$ p' $File|awk '{tmp=""; for(i=4;i<=12;i=i+1){tmp=tmp" "$i};print $1,tmp}' >>tt.dat
