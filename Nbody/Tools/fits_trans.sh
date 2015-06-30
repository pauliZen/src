#Get different stellar types fits images from projected data file
#preprocess: data_proj(_loop).sh

read -p 'data list without .prj and time (dlist)' flist
read -p 'sim2obs path(sim2obs)' sim
read -p 'filter prefix(filter)' filter

[[ -z $flist ]] && flist='dlist'
[[ -z $sim ]] && sim='sim2obs'
[[ -z $filter ]] && filter='filter'

lst=`awk '{print $1}' $flist`

for i in $lst
do
    [ -e $i'.prj' ] || (echo $i'.prj not exist' && exit 1) || exit
    awk '{if ($8<=1&&$9<=1) print $LINE}' $i'.prj' >$i'.prj.ms'
    awk '{if ($8==3||$9==3) print $LINE}' $i'.prj' >$i'.prj.rg'
    awk '{if (($8==5||$8==6)||($9==5||$9==6)) print $LINE}' $i'.prj' >$i'.prj.agb'
    awk '{if (($8>=10&&$8<=12)||($9>=10&&$9<=12)) print $LINE}' $i'.prj' >$i'.prj.wd'
    awk '{if ($8==14||$9==14) {if ($1==0||($8==14&&$9==14)) {tmp=""; for(i=1;i<18;i++) {tmp=tmp" "$i}; tmp=tmp" "(-2.5*log($10+$11)+6)" "$19" "(-2.5*log($10+$11)+6)" "(-2.5*log($10+$11)+6); for(i=22;i<=NF;i++) {tmp=tmp" "$i}; print tmp} else {tmp=""; for(i=1;i<18;i++) {tmp=tmp" "$i}; tmp=tmp" "(-2.5*log($10+$11)+6)" "$19" "(-2.5*log($10+$11)+6)" "$21; for(i=22;i<=NF;i++) {tmp=tmp" "$i}; print tmp}}}' $i'.prj' >$i'.prj.bh'
    awk '{if ($1==1) print $LINE}' $i'.prj' >$i'.prj.bin'
    list='ms rg agb wd bh bin'
#    list='bh'
    clst='B V I'
    for j in $list
    do
	for k in $clst
	do
	    $sim $filter'_'$k $i'.prj.'$j $i'_'$j'_'$k'.fits' $i'_'$j'_'$k'.sb'
	done
    done
    for k in $clst
    do
	$sim $filter'_'$k $i'.prj' $i'_all_'$k'.fits' $i'_all_'$k'.sb'
    done
done
