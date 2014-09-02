Nstar=1000
scrptex='.eps_tex'
newtex='.tab_tex'
nametex='Nstar'$Nstar'_FourNumTable'
namelines=4
datalines=6
nlines=`calc \* $namelines 2`
lines=`calc + $nlines $datalines`
titlename='Nstar & Rbar & RNb & M1 & SSSS & SSSP & SSPP & SPSP & SPPP & PPPP \\\hline'

format='|'
for ((i=1;i<=`calc + $namelines $datalines`;i=i+1))
do
    format=$format'c|'
done

echo '\begin{tabular}{'$format'}'>$nametex$newtex
echo '\hline'>>$nametex$newtex
echo $titlename
echo $titlename>>$nametex$newtex

cat $nametex$scrptex |egrep -i -A $lines 'smash{'$Nstar'\}'>namelist
numline=`cat namelist|wc -l`
lines=`calc + $lines 1`
listnum=`calc / $numline $lines`
start=1
echo 'data number '$listnum
for ((i=0;i<$listnum;i=i+1))
do
    indx=`calc \* $i $lines`
#    echo 'index '$indx
    for ((j=1;j<=$namelines;j=j+1))
    do
	subindx=`calc \* $j 2`
	subindx=`calc + $indx $subindx`
	subindx=`calc - $subindx 1`
	Val[$j]=`cat namelist|head -$subindx|tail -1|cut -d'{' -f4|cut -d'}' -f1`
	Valprint[$j]=${Val[$j]}'&'
#	echo 'subindex '$subindx' '${Valprint[$j]}
    done
    for ((j=1;j<=$datalines;j=j+1))
    do
	subindx=`calc + $nlines 1`
	subindx=`calc + $subindx $j`
	subindx=`calc + $indx $subindx`
	Vald[$j]=`cat namelist|head -$subindx|tail -1|cut -d'{' -f4|cut -d'}' -f1`
#	echo 'subindex '$subindx' '${Vald[$j]}
    done
    if [ $start = 1 ];then
	valt=${Val[$namelines]}
	count=0
	for ((j=1;j<=$datalines;j=j+1))
	do
	    vall[$j]=0
	done
	for ((j=1;j<=$namelines;j=j+1))
	do
	    valn[$j]=${Valprint[$j]}
	done
	start=0
    fi
    if [ $valt = ${Val[$namelines]} ]; then
	for ((j=1;j<=$datalines;j=j+1))
	do
	    vall[$j]=`calc + ${vall[$j]} ${Vald[$j]}`
#	    echo ${vall[$j]}
	done
	count=`calc + $count 1`
	valt=${Val[$namelines]}
    else
	for ((j=1;j<=$datalines;j=j+1))
	do
	    vall[$j]=`calc / ${vall[$j]} $count`
	    vallprint[$j]=${vall[$j]}'&'
	done
#	echo $count
	count=1
	echo ${valn[*]} ${vallprint[*]}'\\\hline'|sed 's/&\\/\\/g'
	echo ${valn[*]} ${vallprint[*]}'\\\hline'|sed 's/&\\/\\/g'>>$nametex$newtex
	for ((j=1;j<=$namelines;j=j+1))
	do
	    valn[$j]=${Valprint[$j]}
	done
	for ((j=1;j<=$datalines;j=j+1))
	do
	    vall[$j]=${Vald[$j]}
#	    echo ${vall[$j]}
	done
	valt=${Val[$namelines]}
    fi
    if [ $i = `calc - $listnum 1` ]; then
	for ((j=1;j<=$datalines;j=j+1))
	do
	    vall[$j]=`calc / ${vall[$j]} $count`
	    vallprint[$j]=${vall[$j]}'&'
	done
	echo ${valn[*]} ${vallprint[*]}'\\\hline'|sed 's/&\\/\\/g'
    fi
done
echo '\end{tabular}'>>$nametex$newtex

if [ -e table ]; then
    mv $nametex$newtex table/
else
    mkdir table
    mv $nametex$newtex table/
fi
rm namelist