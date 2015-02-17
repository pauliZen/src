echo 'TSCALE:'
read tscale

lst=`ls rdist_[0-9]*|cut -d '_' -f2 |sort -n`
rm -f rdist.lst

for i in $lst
do
    echo 'rdist_'$i `calc \* $i $tscale` >> rdist.lst
done


