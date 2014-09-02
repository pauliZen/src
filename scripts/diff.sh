read dsd
ls nbodyo/$dsd>listl
rm -f diglist
for ((i=1;i<`cat listl|wc -l`;i=i+1))
do
    name=`head -$i listl|tail -1`
    echo '** '$name  >>diglist
    diff Nbody6_gpu/$dsd/$name nbodyo/$dsd/$name >>diglist
done

