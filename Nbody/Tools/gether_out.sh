echo 'Which file you want to gether?'
read file
[ -e dirlist ] || exit
[ -e $file.all ] && rm -i $file.all
lst=`cat dirlist`
for i in $lst
do
    cat $i/$file >>$file.all
done
