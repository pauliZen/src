drawrbp=0
drawrmp=0
drawn=0
drawn_simple=1
drawn_all=1
format='pdf'

function c_np()
{
    pline='np n 0 3'
    for i in 0.5 1 2
    do
	npnow=`calc \*n $1 $i`
	pline=$pline" "$npnow
    done
}

function c_nb()
{
    bline='nb n 0 3'
    for i in 0 0.2 0.5
    do
	nbnow=`calc \*n $1 $i`
	bline=$bline" "$nbnow
    done
}

function outl()
{
    case $1 in
	r) echo $rline>>$filename;;
	m) echo $mline>>$filename;;
	b) echo $bline>>$filename;;
	p) echo $pline>>$filename;;
	s) echo $sline>>$filename;;
    esac
}

sline='ns n 0 3 500 1000 2000'
mline='m1+10*p1 n 0 4 11 12 21 22'
rline='rbar d 0.001 3 0.5 1.0 2.0'

figpath='/home/lwang/Dropbox/Datas/Planets/step3_'$format'/'

[ -e $figpath ] || mkdir $figpath

#draw fix->ns
for ns in 500 1000 2000
do
    c_np $ns
    c_nb $ns
    #draw fix m1
    if [ $drawrbp = 1 ]; then
	for i in 1 2
	do
	#draw fix p1
	    for j in 1 2
	    do
		fignameprefix='ns'$ns'_m'$i'p'$j
		filenameprefix='step3_'$fignameprefix
		for ord in rbp bpr prb
		do
		    filename=$filenameprefix$ord'.lst'
		    echo 'm1=='$i'&&p1=='$j'&&ns=='$ns >$filename
		    outl `echo $ord|cut -c1`
		    outl `echo $ord|cut -c2`
		    outl `echo $ord|cut -c3`
		    drawstep3 -l $figpath $fignameprefix$ord'.'$format $filename 0
		    drawstep3 -l $figpath $fignameprefix$ord'_r.'$format $filename 1
		done
    	    done
	done
    fi
    #draw fix nb
    if [ $drawrmp = 1 ]; then
	for i in `echo $bline|cut -d' ' -f5-7`
	do
	    fignameprefix='ns'$ns'_nb'$i
	    filenameprefix='step3_'$fignameprefix
	    for ord in rmp mrp pmr
	    do
		filename=$filenameprefix$ord'.lst'
		echo 'nb=='$i'&&ns=='$ns >$filename
		outl `echo $ord|cut -c1`
		outl `echo $ord|cut -c2`
		outl `echo $ord|cut -c3`
		drawstep3 -l $figpath $fignameprefix$ord'.'$format $filename 0
		drawstep3 -l $figpath $fignameprefix$ord'_r.'$format $filename 1
	    done
	done
    fi
done

if [ $drawn = 1 ]; then
#draw fix m1
    for i in 1 2
    do
    #draw fix p1
	for j in 1 2
	do
	    fignameprefix='m'$i'p'$j
	    filenameprefix='step3_'$fignameprefix
	    filename=$filenameprefix'.lst'
	    echo 'm1=='$i'&&p1=='$j >$filename
	    echo $rline >>$filename
	    echo 'ns+nb n 0 9 500 600 750 1000 1200 1500 2000 2400 3000' >>$filename
	    echo 'np n 0 5 250 500 1000 2000 4000' >>$filename
	    drawstep3 -l $figpath $fignameprefix'.'$format $filename 0
	    drawstep3 -l $figpath $fignameprefix'_r.'$format $filename 1
	done
    done
fi

if [ $drawn_simple = 1 ]; then
    for i in 1 2
    do
	for j in 1 2
	do
	    fignameprefix='np1000m'$i'p'$j
	    filenameprefix='step3_'$fignameprefix
	    filename=$filenameprefix'.lst'
	    echo 'np==1000&&m1=='$i'&&p1=='$j >$filename
	    echo $rline >>$filename
	    echo 'ns n 0 3 500 1000 2000' >>$filename
	    echo 'nb n 0 6 0 100 250 200 500 400 1000' >>$filename
	    drawstep3 -l $figpath $fignameprefix'.'$format $filename 0
	    drawstep3 -l $figpath $fignameprefix'_r.'$format $filename 1
	done
    done
fi

if [ $drawn_all = 1 ]; then
    fignameprefix='np1000'
    filename='step3_'$fignameprefix'.lst'
    echo 'np==1000' >$filename
    echo $rline >>$filename
    echo 'm1+10*p1 n 0 4 11 12 21 22' >>$filename
    echo 'ns+nb n 0 9 500 600 750 1000 1200 1500 2000 2400 3000' >>$filename
    drawstep3 -l $figpath $fignameprefix'.'$format $filename 0
    drawstep3 -l $figpath $fignameprefix'_r.'$format $filename 1
fi
