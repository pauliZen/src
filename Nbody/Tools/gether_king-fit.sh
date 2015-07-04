# Gether king-fitting result from king-fit-lum.plt
lst=`ls dlst_split.*.err`
file='king-fit-lum.dat'
rm -f $file
for i in $lst
do
    egrep ' Time' $i|cut -d' ' -f10-30 >> $file
done
