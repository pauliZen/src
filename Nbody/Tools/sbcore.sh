#get core radius for list of files
#Preprogram: sbp.sh

[ -e sbcore.py ] || exit

tscale=0.5506

rm -f sbcore.[VBI]

function sloop()
{
    lst=`ls data_*.sb.$1`
    for j in $lst
    do
	time=`echo $j|sed -e 's/data.//' -e "s/.sb.$1//"`
	time=`calc \* $time $tscale`
	python sbcore.py $j $time >>sbcore.$1 2>>sbcore.err
    done
}


sloop V &
sloop B &
sloop I &

