ls |egrep ^[0-9]+_[0-9\.]+_[0-9\.]+_[0-9\.]+_[0-9]+_[0-9]+>v4list
ls |egrep ^[0-9]+_[0-9\.]+_[0-9\.]+_[0-9\.]+_[0-9]+$>v0list

[ -d root ] || mkdir root

for i in 0 4
do
    gli=7
    [ $i = 0 ] && gli=5
    for j in 500 1000 2000
    do
 	for jj in 0.5 1 2
 	do
 	    for jjj in 0 0.2 0.5
 	    do
		for jjjj in 0.5 1 2
		do
		    jjdj=$jjj
		    [[ $jjj == "0.2" ]] && jjdj=0\\.2
 		    rm -f $j'_'$jj'_'$jjj'_'$jjjj'v'$i.log
 		    cat v$i'list' |egrep ^$j'_'$jj'_'$jjdj'_'$jjjj'_'|awk '{print $1" "$1}'|sed "s/_/ /g$gli">root/$j'_'$jj'_'$jjj'_'$jjjj'v'$i.lst
 		    echo 'now '$j'_'$jj'_'$jjj'_'$jjjj'v'$i.log
 		    celist $i root/$j'_'$jj'_'$jjj'_'$jjjj'v'$i.lst root/$j'_'$jj'_'$jjj'_'$jjjj'v'$i'_celist'.root 1>>root/$j'_'$jj'_'$jjj'_'$jjjj'v'$i.log 2>>root/$j'_'$jj'_'$jjj'_'$jjjj'v'$i.log
		done
 	    done
 	done
     done
 done

# for jj in 0.5 1 2
# do
#     for jjj in 0 0.2 0.5
#     do
# 	for jjjj in 0.5 1 2
# 	do
# 	    rm -f '2000_'$jj'_'$jjj'_'$jjjj'v4.log'
# 	    cat v4list |egrep ^'2000_'$jj'_'$jjj'_'$jjjj'_'|awk '{print $1" "$1}'|sed "s/_/ /g7">root/'2000_'$jj'_'$jjj'_'$jjjj'v4.lst'
# 	    echo 'now 2000_'$jj'_'$jjj'_'$jjjj'v4.log'
# 	    celist 4 root/2000_$jj'_'$jjj'_'$jjjj'v4.lst' root/2000_$jj'_'$jjj'_'$jjjj'v4_celist.root' 1>>root/2000_$jj'_'$jjj'_'$jjjj'v4.log' 2>>root/2000_$jj'_'$jjj'_'$jjjj'v4.log'
# 	done
#     done
# done
