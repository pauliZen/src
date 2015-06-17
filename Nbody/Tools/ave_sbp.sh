# get surfacedensity and average value (require dlist.*)
# Preprogram: data_proj.sh
[ -e ave_sbp.py ] || exit
[ -e ave_color.py ] || exit
[ -e ave_sbcore.py ] || exit
#[ -e surfacedensity.py ] || exit

echo 'tscale ='
read tscale

ic=`ls dlist.*|wc -l`

rm -f sbcore.[VBI]

for ((i=0;i<$ic;i=i+1))
do
    lst=`cat dlist.$i`
    tave=0
    nc=0
    for j in $lst
    do
#	echo "sbp $j"
	time=`echo $j|cut -d'_' -f2`
	tave=`calc + $tave $time`
	let nc++
#	python surfacedensity.py $j.prj 'V' 100 25 0.1 $j.sb.V 5800 
#	python surfacedensity.py $j.prj 'I' 100 25 0.1 $j.sb.I 5800 
#	python surfacedensity.py $j.prj 'B' 100 25 0.1 $j.sb.B 5800
    done
    tave=`calc / $tave $nc`
    echo "ave_sbp $i"
    awk '{print $1".sb.V"}' dlist.$i >dsbV.$tave 
    awk '{print $1".sb.B"}' dlist.$i >dsbB.$tave 
    awk '{print $1".sb.I"}' dlist.$i >dsbI.$tave 
    python ave_sbp.py dsbV.$tave sbave.$tave.V V
    python ave_sbp.py dsbI.$tave sbave.$tave.B B
    python ave_sbp.py dsbB.$tave sbave.$tave.I I
    python ave_sbcore.py dsbV.$tave $tscale >>sbcore.V
    python ave_sbcore.py dsbI.$tave $tscale >>sbcore.I
    python ave_sbcore.py dsbB.$tave $tscale >>sbcore.B
    python ave_color.py sbave.$tave colorave.$tave
done
