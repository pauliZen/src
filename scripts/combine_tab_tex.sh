nstar=1000
twoname='Nstar'$nstar'_TwNumTable.tab_tex'
triname='Nstar'$nstar'_TriNumTable.tab_tex'
forname='Nstar'$nstar'_FourNumTable.tab_tex'
titlename='Nstar & Rbar & RNb & M1 '
outname='Nstar'$nstar'_NumTable.tab_tex'
outrname='Nstar'$nstar'_NRSPSSTable.tab_tex'

egrep -i '[0-9]+&' $twoname |cut -d'&' -f1-4>namelist

format='|'
formatr='|'
tablelines=10
tablerlines=10
for ((i=1;i<=$tablelines;i=i+1))
do
    format=$format'c|'
done

for ((i=1;i<=$tablerlines;i=i+1))
do
    formatr=$formatr'c|'
done

echo '\begin{tabular}{'$format'}'>$outname
echo '\hline'>>$outname

echo '\begin{tabular}{'$formatr'}'>$outrname
echo '\hline'>>$outrname

start=1
for ((i=-1;i<=`cat namelist|wc -l`;i=i+2))
do
    if [ $start = 1 ];then
	nowname=$titlename
	ss='SS'
	sp='SP'
	pp='PP'
	sss='SSS'
	ssp='SSP'
	spp='SPP'
	pss='PSS'
	psp='PSP'
	ppp='PPP'
	ssss='SSSS'
	sssp='SSSP'
	sspp='SSPP'
	spsp='SPSP'
	sppp='SPPP'
	pppp='PPPP'

	rss='RSS'
	rsp='RSP'
	rpp='RPP'
	rsss='RSSS'
	rssp='RSSP'
	rspp='RSPP'
	rpss='RPSS'
	rpsp='RPSP'
	rppp='RPPP'
	rssss='RSSSS'
	rsssp='RSSSP'
	rsspp='RSSPP'
	rspsp='RSPSP'
	rsppp='RSPPP'
	rpppp='RPPPP'

	start=0
    else
	nowname=`cat namelist|head -$i|tail -1`
	ss=`egrep "$nowname" $twoname|cut -d'&' -f5`
	sp=`egrep "$nowname" $twoname|cut -d'&' -f6`
	pp=`egrep "$nowname" $twoname|cut -d'&' -f7`
	sss=`egrep "$nowname" $triname|cut -d'&' -f5`
	ssp=`egrep "$nowname" $triname|cut -d'&' -f6`
	spp=`egrep "$nowname" $triname|cut -d'&' -f7`
	pss=`egrep "$nowname" $triname|cut -d'&' -f8`
	psp=`egrep "$nowname" $triname|cut -d'&' -f9`
	ppp=`egrep "$nowname" $triname|cut -d'&' -f10`
	ssss=`egrep "$nowname" $forname|cut -d'&' -f5`
	sssp=`egrep "$nowname" $forname|cut -d'&' -f6`
	sspp=`egrep "$nowname" $forname|cut -d'&' -f7`
	spsp=`egrep "$nowname" $forname|cut -d'&' -f8`
	sppp=`egrep "$nowname" $forname|cut -d'&' -f9`
	pppp=`egrep "$nowname" $forname|cut -d'&' -f10`


	ss=`calc + $ss 0 0`
	sp=`calc + $sp 0 0`
	pp=`calc + $pp 0 0`
	sss=`calc + $sss 0 0`
	ssp=`calc + $ssp 0 0`
	spp=`calc + $spp 0 0`
	pss=`calc + $pss 0 0`
	psp=`calc + $psp 0 0`
	ppp=`calc + $ppp 0 0`
	ssss=`calc + $ssss 0 0`
	sssp=`calc + $sssp 0 0`
	sspp=`calc + $sspp 0 0`
	spsp=`calc + $spsp 0 0`
	sppp=`calc + $sppp 0 0`
	pppp=`calc + $pppp 0 0`

	rss=$ss
	rsp=`calc /p 3 $sp $ss`
	rpp=`calc /p 3 $pp $ss`
	rsss=`calc /p 3 $sss $ss`
	rssp=`calc /p 3 $ssp $ss`
	rspp=`calc /p 3 $spp $ss`
	rpss=`calc /p 3 $pss $ss`
	rpsp=`calc /p 3 $psp $ss`
	rppp=`calc /p 3 $ppp $ss`
	rssss=`calc /p 3 $ssss $ss`
	rsssp=`calc /p 3 $sssp $ss`
	rsspp=`calc /p 3 $sspp $ss`
	rspsp=`calc /p 3 $spsp $ss`
	rsppp=`calc /p 3 $sppp $ss`
	rpppp=`calc /p 3 $pppp $ss`
    fi
    echo $nowname '&' $ss '&' $sp '&' $sss '&' $ssp '&' $pss '&' $ssss '\\\hline'
    echo $nowname '&' $ss '&' $sp '&' $sss '&' $ssp '&' $pss '&' $ssss '\\\hline'>>$outname

    echo $nowname '&' $rss '&' $rsp '&' $rsss '&' $rssp '&' $rpss '&' $rssss '\\\hline'
    echo $nowname '&' $rss '&' $rsp '&' $rsss '&' $rssp '&' $rpss '&' $rssss '\\\hline'>>$outrname

done
echo '\end{tabular}'>>$outname
echo '\end{tabular}'>>$outrname
echo 'end'
rm namelist