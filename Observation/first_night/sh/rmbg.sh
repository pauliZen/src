lines=`cat Uodfse.lst|wc -l`
for ((i=1;i<=$lines;i=i+1))
do
    file=`head -$i Uodfse.lst|tail -1`
    newfile=`echo $file|sed 's/\.fit/b\.fit/g'`
    sextractor -c default.sex $file -CHECKIMAGE_TYPE -BACKGROUND -CHECKIMAGE_NAME $newfile
#    echo $newfile $i
done
