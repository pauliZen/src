#use splited index list to run select-stars-log
#for select-star-log
rootname='run-020-020-1mil'
treename='SdEvsEsGT12_'
treetitle="Select_stars_by_|dE/E_start|>exp(0.2)_part"
indexname="dE_scan_150to0.0"  #"index name before '.'"
filenum=7  #"index file number(should less then 10)"
timeend=150
bhsplitnum=8

for ((i=0;i<$filenum;i++))
do
    echo "Now:"$i
    select-star-log $rootname $treename$i $treetitle$i $indexname$i $timeend $bhsplitnum
done
